#ifndef GAMELIST_HH
#define GAMELIST_HH

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

#include <string>
#include <vector>

#include <pthread.h>

#include <corps/gamelist-impl.hh>


class CorbaException;
class Game_Wrapper;


class _GameList : public GameList_Impl
{
public:
  _GameList() throw();
  virtual ~_GameList() throw();

  void dump_to_screen() throw();

private:
  virtual ::GameList get_list() throw(CorbaException);
  virtual string _register(Game_Wrapper g) throw(CorbaException);
  virtual void _unregister(const string &id) throw(CorbaException);

  typedef struct { Game_Wrapper game; string id; } GameList_s;
  typedef vector<GameList_s> GameList_t;
  GameList_t game_list;
  pthread_mutex_t game_list_lock;
};

#endif // GAMELIST_HH
