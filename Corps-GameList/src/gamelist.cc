/*  GameList implementation for GameList server
    Copyright (C) 1998-99 Sebastian Rittau

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <iostream>

#include <unistd.h>
#include <libintl.h>

#include <corps/corbaexception.hh>
#include <corps/orb.hh>
#include <corps/roleplaying.hh>
#include <corps/tools.hh>

#include "gamelist.hh"


extern CORPS_ORB *orb;


_GameList::_GameList() throw() :
  GameList_Impl()
{
  pthread_mutex_init(&game_list_lock, 0);
}


_GameList::~_GameList() throw()
{
  while(pthread_mutex_destroy(&game_list_lock))
    sleep(1);
}


void _GameList::dump_to_screen() throw()
{
  pthread_mutex_lock(&game_list_lock);
  cerr << endl << gettext("=== start database dump ===") << endl;

  GameList_t::size_type pos = 0;
  while(pos < game_list.size())
    {
      string id;
      Game_Wrapper &g = game_list[pos].game;
      try { id = orb->object_to_string(g.get_CORBA_object()); }
      catch(...) { id = gettext("<error>"); }
      cerr << "\n(" << pos + 1 << ") " << g.get_name() << endl << id << endl;
      pos++;
    }

  cerr << endl << gettext("=== end database dump ===") << endl;
  pthread_mutex_unlock(&game_list_lock);
}


::GameList _GameList::get_list() throw(CorbaException)
{
  pthread_mutex_lock(&game_list_lock);

  ::GameList list;

  GameList_t::size_type pos = 0;
  while(pos < game_list.size())
    list.insert(list.end(), game_list[pos++].game);

  pthread_mutex_unlock(&game_list_lock);

  return list;
}


string _GameList::_register(Game_Wrapper g) throw(CorbaException)
{
  pthread_mutex_lock(&game_list_lock);

  // check, if game was already registered before
  GameList_t::size_type pos = 0;
  while(pos < game_list.size())
    {
      if(g == game_list[pos].game)
	throw CorbaException(RolePlaying::GameList::AlreadyRegistered());
      pos++;
    }

  // add entry to list
  const time_t t = time(0); //FIXME: better cookie
  string id = ctime(&t); //FIXME: dito
  GameList_s entry = { g, id };
  game_list.insert(game_list.end(), entry);

  pthread_mutex_unlock(&game_list_lock);

  // print message
  try
    {
      cerr << endl
	   << insert_text(gettext("registered game: %s\n"),
			  orb->object_to_string(g.get_CORBA_object()));
    }
  catch(...) {}

  return id;
}


// This operation is flagged "oneway", so there is no point in throwing
// exceptions.
void _GameList::_unregister(const string &id) throw(CorbaException)
{
  pthread_mutex_lock(&game_list_lock);

  GameList_t::size_type pos = 0;
  while(pos < game_list.size())
    {
      if(game_list[pos].id == id)
	{
	  game_list.erase(game_list.begin() + pos);

	  // print message
	  try
	    {
	      cerr << endl
		   << insert_text(gettext("unregistered game: %s\n"),
				  orb->object_to_string(game_list[pos].game.get_CORBA_object()));
	    }
	  catch(...) {}

	  pthread_mutex_unlock(&game_list_lock);
	  return;
	}
      pos++;
    }

  // we haven't registered this game: somebody is trying to cheat
  pthread_mutex_unlock(&game_list_lock);

  cerr << endl << insert_text(gettext("WARNING: invalid id: %s\n"), id);
}
