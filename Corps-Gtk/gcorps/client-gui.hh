#ifndef CLIENT_GUI_HH
#define CLIENT_GUI_HH

/*  Client GUI class for RPGGame
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

#include <pthread.h>

#include <gtk--sig.h>

#include "gui_playfield.hh"


class Client;
class Exception;
class Game_Wrapper;
class GameList_Wrapper;
class GUI_BusyRequester;
class GUI_FileRequester;
class GUI_GameChooser;
class GUI_GameWindow;
class GUI_StringRequester;


class Client_GUI : public virtual Gtk_Signal_Base
{
public:
  /*** Constructors/Destructor ***/
  Client_GUI(Client &parent) throw();
  ~Client_GUI() throw();

  /*** Support Functions ***/
  void show() throw();
  // void'ed version of leave_game()
  void leave() throw() { leave_game(); }
  // it is save to call leave_game() even if we are not currently connected
  // this returns false if leaving was not possible
  bool leave_game() throw();

  /*** text/plain MIME Handler ***/
  void print_text(const string &text) throw();
  string request_string(const string &what) throw();
  string request_text(const string &what) throw();
  void kick(const string &reason) throw();

private:
  void delete_client() throw();
  void close_windows() throw();
  Client &client;

  void init_print_to_game(string text) throw();
  void print_to_game(string text) throw();
  static void *try_print_to_game(void *s) throw();

  void init_connecting() throw(); // asynchronous version of connect()
  void connect() throw();
  static void *try_connect(void *o) throw();

  void init_opening() throw(); // asynchronous version of open()
  void open() throw();
  static void *try_open(void *o) throw();

  // requests the user to choose a game from a list
  Game_Wrapper *get_game_from_list(GameList_Wrapper &glw) throw(Exception);
  string request_game_filename() throw();
  void connect_to_named_game(const string &filename) throw();
  void connect_to_game(Game_Wrapper &game) throw(Exception);

  // GUI objects
  GUI_GameWindow *game_win;
  GUI_Playfield playfield;

  GUI_FileRequester   *file_req;
  GUI_BusyRequester   *busy_req;
  GUI_StringRequester *gameid_req;
  GUI_GameChooser     *gamelist_req;

  // locks
  pthread_mutex_t connect_lock;   // locked while connecting or opening a game
  pthread_mutex_t requester_lock; // locked, whenever a modal requester is open
};

#endif // CLIENT_GUI_HH
