/*  Implementation of game class for textserv
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
#include <pthread.h>
#include <libintl.h>

#include <corps/corba.hh>
#include <corps/corbaexception.hh>
#include <corps/ch-history-wrapper.hh>
#include <corps/orb.hh>
#include <corps/system-impl.hh>
#include <corps/tools.hh>

#include "arghandler.hh"
#include "game.hh"
#include "system.hh"


extern ArgHandler *args;
extern CORPS_ORB  *orb;


Game::Game() throw() :
  Game_Impl(0),

  system_impl(0),
  client_list()
{
  system_impl = new System;

  _name = args->getGameName();
  _description = args->getGameDescription();
  _system = system_impl;
  game_type = GTMastered | GTMultiPlayer;

  pthread_mutex_init(&client_list_lock, 0);

  system_impl->_obj_is_ready(orb->getBOA());
}


Game::~Game() throw()
{
  // kick() all clients still connected
  pthread_mutex_lock(&client_list_lock);
  ClientList::size_type pos = 0;
  while(pos < client_list.size())
    {
      client_list[pos].client.kick("server shutdown"); //FIXME: language?
      pos++;
    }
  pthread_mutex_unlock(&client_list_lock);

  while(pthread_mutex_destroy(&client_list_lock))
    sleep(1);

  if(system_impl)
    system_impl->_dispose();
}


// FIXME: Currently, it is possible that multiple client acquire the same nick
// since the client-list gets unlocked while
string Game::_join(Client_Wrapper client) throw(CorbaException)
{
  try
    {
      threaded_output(gettext("client trying to join game"));

      // get history handler
      CH_History_Wrapper history =
	CH_History_Wrapper(client.get_handler("HISTORY", 0));

      // set-up client
      ClientEntry entry = {
	client,               // client
	history,              // history wrapper
	create_cookie(),      // cookie
	string(),             // nick
	0                     // error count
      };

      // print welcome message
      pthread_mutex_lock(&client_list_lock); // lock client list while
                                             // building nick list
      string s("Welcome to the simple CORPS text-only server\n"
	       "Connected clients: "); //FIXME: language
      s += num2str(client_list.size());
      s += '\n';
      ClientList::size_type pos = 0;
      while(pos < client_list.size())
	{
	  s += client_list[pos].nick;
	  pos++;
	  if(pos < client_list.size())
	    s += ", ";
	}
      pthread_mutex_unlock(&client_list_lock); // done with client list
      entry.history.append_text(s);

      // get nick name
      //FIXME      entry.history.request_string("Please enter your nickname.", entry.nick); //FIXME:language
      entry.nick = "test"; //FIXME

      // check the nick name and re-request if it's already in use or invalid
      pthread_mutex_lock(&client_list_lock);
      while(!check_nick(entry.nick))
	{
	  // temporarily unlock client list
	  pthread_mutex_unlock(&client_list_lock);
	  //FIXME	  entry.history.request_string("The nickname you chose is either already used or invalid. Please retry.", entry.nick); //FIXME:language
	  pthread_mutex_lock(&client_list_lock);
	}

      // insert client into list
      client_list.insert(client_list.end(), entry);

      // unlock client list
      pthread_mutex_unlock(&client_list_lock);

      // tell everybody that a new user has connected
      string tmp(entry.nick); //FIXME:language
      tmp.append(" has connected");
      broadcast(tmp);

      threaded_output(insert_text(gettext("%s joined game"), entry.nick));

      return entry.cookie;

    }
  catch(CorbaException e)
    {
      if(RolePlaying::ClientHandler::NoSuchHandler::_downcast(&e))
	throw CorbaException(RolePlaying::Game::FeatureMissing());
      throw e;
    }
  catch(...) { throw; } //FIXME
}


// RolePlaying::Game::leave() is flagged "oneway" so there is no point in
// throwing exceptions.
void Game::_leave(const string &id) throw(CorbaException)
{
  threaded_output(gettext("client trying to leave game"));

  pthread_mutex_lock(&client_list_lock);

  // traverse the list of connected clients
  ClientList::size_type pos = 0;
  while(pos < client_list.size())
    {
      if(client_list[pos].cookie == id)
	{
	  threaded_output(insert_text(gettext("%s has left game"),
				      client_list[pos].nick));
	  client_list.erase(client_list.begin() + pos);
	  break;
	}
      pos++;
    }

  pthread_mutex_unlock(&client_list_lock);

  threaded_output(gettext("client not found"));
}

/****************************************/

void Game::broadcast(const string &text) throw()
{
  threaded_output(insert_text(gettext("broadcasting text: %s"), text));

  pthread_mutex_lock(&client_list_lock);

  ClientList::size_type pos = 0;
  while(pos < client_list.size())
    {
      ClientEntry &entry = client_list[pos];
      do
	{
	  try
	    {
	      entry.history.append_text(text);
	      entry.error_count = 0;
	    }
	  catch(CorbaException e)
	    {
	      threaded_warning(e.get_error_string());
	      entry.error_count++;
	    }
	}
      while(entry.error_count > 0 && entry.error_count < 10);
      pos++;
    }

  pthread_mutex_unlock(&client_list_lock);
}

/************************************/

// Client list must be protected against access by other threads by caller!
bool Game::check_nick(const string &nick) const throw()
{
  // check, if nick is valid
  if(nick.empty() || nick.size() > 10)
    return false;

  for(string::size_type pos = 0; pos < nick.size(); pos++)
    if(!isalnum(nick[pos]))
      return false;

  // check, if nick does already exits
  bool ok = true;
  ClientList::size_type pos = 0;
  while(pos < client_list.size() && ok == true)
    {
      if(client_list[pos].nick == nick)
	ok = false;
      pos++;
    }

  return ok;
}
