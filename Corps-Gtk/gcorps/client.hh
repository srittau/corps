#ifndef CLIENT_HH
#define CLIENT_HH

/*  Client class for GCorps
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

/*
    WARNING: Allocate this class with "new" only. It may destroy itself!
*/

#include <string>
#include <vector>

#include "client-gui.hh"

class Client_I;
class CorbaException;
class Exception;
class Game_Wrapper;


class Client {
public:
  Client() throw(Exception);
  ~Client() throw();

  Client_GUI &getGUI() throw() { return c_gui; };

  void delete_client() throw();
  // delete all client objects
  static void delete_all() throw();

  void connect_to_game(const Game_Wrapper &game) throw(CorbaException);
  void kick(const string &reason) throw();

  void print_to_game(const string &text) throw(Exception);

private:
  // client list management
  typedef vector<Client *> client_list_type;
  static client_list_type client_list;
  void delete_from_client_list() throw();
  bool listed;

  Client_I *cl_impl;
  Client_GUI c_gui;

  Game_Wrapper *game;
};

#endif // CLIENT_HH
