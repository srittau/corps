#ifndef GAME_WRAPPER_HH
#define GAME_WRAPPER_HH

/*  Interface for Game-Wrapper
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
#include <vector>

#include "roleplaying.hh"
#include "system-wrapper.hh"

class Client_Impl;
class CorbaException;
class Exception;


class Game_Wrapper
{
public:
  // mastered by a human person
  static const unsigned int Type_Mastered = 1;
  // game for multiple players
  static const unsigned int Type_MultiPlayer = 2;
  // one player may play multiple characters
  static const unsigned int Type_MultiCharacter = 4;

  Game_Wrapper() throw();
  Game_Wrapper(const RolePlaying::Game_var &go) throw(CorbaException);

  Game_Wrapper &operator=(const RolePlaying::Game_var &go) throw(CorbaException);
  bool operator==(const Game_Wrapper &o) throw();

  operator RolePlaying::Game_var &() throw() { return game; }
  operator const RolePlaying::Game_var &() const throw() { return game; }

  const string &get_name() const throw() { return name; }
  const string &get_description() const throw() { return description; }
  const System_Wrapper &get_system() const throw() { return system; }
  bool is_mastered() const throw() { return(type & Type_Mastered); }
  bool is_multi_player() const throw() { return(type & Type_MultiPlayer); }
  bool is_multi_character() const throw() { return(type & Type_MultiCharacter); }
  const string &join(RolePlaying::Client_ptr cl) throw(Exception);
  // leave with id last returned by join()
  void leave() throw(Exception);
  void leave(const string &id) throw(Exception);

private:
  void attrs_from_object() throw(CorbaException);

  RolePlaying::Game_var game;

  string name;
  string description;
  System_Wrapper system;
  unsigned int type;

  string cookie;
};

typedef vector<Game_Wrapper> GameList;

#endif // GAME_WRAPPER_HH
