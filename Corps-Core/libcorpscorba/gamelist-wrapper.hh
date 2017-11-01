#ifndef GAMELIST_WRAPPER_HH
#define GAMELIST_WRAPPER_HH

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

#include <string>

#include "game-wrapper.hh"
#include "roleplaying.hh"

class CorbaException;
class Game_Impl;

typedef vector<Game_Wrapper> GameList;


class GameList_Wrapper
{
public:
  GameList_Wrapper() throw();
  GameList_Wrapper(const RolePlaying::GameList_var &o) throw(CorbaException);

  GameList_Wrapper &operator=(const RolePlaying::GameList_var &go)
    throw(CorbaException);
  bool operator==(const GameList_Wrapper &o) throw();

  operator RolePlaying::GameList_var &() throw() { return gamelist; }
  operator const RolePlaying::GameList_var &() const throw()
  { return gamelist; }

  GameList get_list() throw(CorbaException);

  const string &_register(RolePlaying::Game_ptr game) throw(CorbaException);
  // unregister last game registered with _register()
  void unregister() throw(Exception);
  void unregister(const string &i) throw(CorbaException);

private:
  RolePlaying::GameList_var gamelist;
  string id;
};

#endif // GAMELIST_WRAPPER_HH
