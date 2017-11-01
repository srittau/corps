#ifndef GUI_GAMEWINDOW_HH
#define GUI_GAMEWINDOW_HH

/*  Interface for gui_gamewindow.cc
    Copyright (C) 1998 Sebastian Rittau

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

#include <gtk--/box.h>
#include <gtk--/menu.h>
#include <gtk--/menubar.h>
#include <gtk--/menuitem.h>
#include <gtk--/window.h>

class Client_GUI;
class GUI_Playfield;


class GUI_GameWindow : public Gtk_Window
{
public:
  GUI_GameWindow(GUI_Playfield &pf) throw();

  // true if somebody tries to connect to/open a game in this window
  void connecting(bool yes) throw();
  // true if game is openend in this window
  void connected(bool yes) throw();

  Signal0 connect;
  Signal0 open;
  Signal0 leave;
  Signal0 delete_client;

protected:
  virtual gint delete_event_impl(GdkEventAny *) throw();

private:
  bool is_connecting;

  void new_window() throw();
  void open_game() throw();
  void connect_to_game() throw();
  void leave_game() throw();
  void close() throw();
  void exit() throw();
  void about() throw();

  Gtk_VBox main_box;

  Gtk_MenuBar menu_bar;
  Gtk_Menu file_menu;
  Gtk_MenuItem file_menu_item;
  Gtk_MenuItem new_menu_item;
  Gtk_MenuItem open_menu_item;
  Gtk_MenuItem connect_menu_item;
  Gtk_MenuItem leave_menu_item;
  Gtk_MenuItem separator_item1;
  Gtk_MenuItem close_menu_item;
  Gtk_MenuItem exit_menu_item;
  Gtk_Menu help_menu;
  Gtk_MenuItem help_menu_item;
  Gtk_MenuItem about_menu_item;

  GUI_Playfield &playfield;
};

#endif // GUI_GAMEWINDOW_HH
