#ifndef GAMELIST_HH
#define GAMELIST_HH

/*  Simple GameList implementation for GCorps
    Copyright (C) 1999 Sebastian Rittau

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

#include <string>

#include <pthread.h>

#include <corps/game-wrapper.hh>
#include <corps/gamelist-impl.hh>


class CorbaException;


class _GameList : public GameList_Impl
{
public:
  _GameList() throw();
  virtual ~_GameList() throw();

  Game_Wrapper *wait_for_registry() throw();
  void abort() throw();

private:
  // CORBA methods
  // just throws NO_IMPLEMENT
  virtual ::GameList get_list() throw(CorbaException);
  virtual string _register(Game_Wrapper g) throw(CorbaException);
  // flagged "one-way" - does nothing
  virtual void _unregister(const string &id) throw(CorbaException);

  Game_Wrapper game;
  bool game_aborted;
  pthread_cond_t game_registered;
  pthread_mutex_t lock;
};

#endif // GAMELIST_IMPL_HH
