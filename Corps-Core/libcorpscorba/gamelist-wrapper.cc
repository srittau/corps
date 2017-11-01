/*  Handling of game lists
    Copyright (C) 1999-2000 Sebastian Rittau

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
#include <string>

#include "corbaexception.hh"
#include "game-impl.hh"
#include "gamelist-wrapper.hh"


GameList_Wrapper::GameList_Wrapper() throw() :
  gamelist(),
  id()
{
}


GameList_Wrapper::GameList_Wrapper(const RolePlaying::GameList_var &o)
  throw(CorbaException) :
  gamelist(o),
  id()
{
}


GameList_Wrapper &GameList_Wrapper::operator=(const RolePlaying::GameList_var &go)
  throw(CorbaException)
{
  gamelist = go;
  id = "";

  return *this;
}


bool GameList_Wrapper::operator==(const GameList_Wrapper &o) throw()
{
  return gamelist->_is_equivalent(o.gamelist);
}


GameList GameList_Wrapper::get_list() throw(CorbaException)
{
  RolePlaying::GameList::GList *list;
  GameList glist;

  try
    {

      // first, build list of available games
      list = gamelist->list();

      // convert list
      unsigned int gamepos = 0;
      for(unsigned int pos = 0; pos < list->length(); pos++)
	{
	  Game_Wrapper game((*list)[pos]);
	  glist.insert(glist.end(), game);
	}

    }
  catch(CORBA::SystemException e) { throw CorbaException(e); }

  return glist;
}


const string &GameList_Wrapper::_register(RolePlaying::Game_ptr game)
  throw(CorbaException)
{
  try
    {
      char *ret = gamelist->_cxx_register(game);
      id = ret;
      CORBA::string_free(ret);
    }
  catch(CORBA::Exception e) { throw CorbaException(e); }

  return id;
}


void GameList_Wrapper::unregister() throw(Exception)
{
  if(id.empty())
    throw Exception(Exception::INTERNAL_ERROR);

  try { gamelist->unregister(id.c_str()); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}


void GameList_Wrapper::unregister(const string &i) throw(CorbaException)
{
  try { gamelist->unregister(i.c_str()); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}
