/*  Simple GameList implementation for GCorps
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

#include <omniORB2/CORBA.h>

#include <corps/corbaexception.hh>
#include <corps/orb.hh>

#include "gamelist.hh"


extern CORPS_ORB *orb;


_GameList::_GameList() throw() :
  GameList_Impl(),

  game_aborted(false)
{
  pthread_mutex_init(&lock, 0);
  pthread_cond_init(&game_registered, 0);
}


_GameList::~_GameList() throw()
{
  while(pthread_mutex_destroy(&lock))
    sleep(1);
  while(pthread_cond_destroy(&game_registered))
    sleep(1);
}


::GameList _GameList::get_list() throw(CorbaException)
{
  throw CorbaException(CORBA::NO_IMPLEMENT());
}


string _GameList::_register(Game_Wrapper g) throw(CorbaException)
{
  if(pthread_mutex_trylock(&lock))
    throw CorbaException(CORBA::NO_PERMISSION());
  game = g;
  pthread_cond_broadcast(&game_registered);
  pthread_mutex_unlock(&lock);
}


// flagged "one-way" - do nothing
void _GameList::_unregister(const string &id) throw(CorbaException)
{
}


Game_Wrapper *_GameList::wait_for_registry() throw()
{
  pthread_mutex_lock(&lock);

  // first check if waiting was already aborted
  if(game_aborted)
    return 0;
  // wait for registering or aborting
  pthread_cond_wait(&game_registered, &lock);
  // get game-id (if waiting was not aborted)
  Game_Wrapper *g;
  if(!game_aborted)
    g = new Game_Wrapper(game);

  pthread_mutex_unlock(&lock);

  return g;
}


void _GameList::abort() throw()
{
  pthread_mutex_lock(&lock);
  game_aborted = true;
  pthread_cond_broadcast(&game_registered);
  pthread_mutex_unlock(&lock);
}
