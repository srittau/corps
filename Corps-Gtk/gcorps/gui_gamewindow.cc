/*  GUI_GameWindow class
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

#include <config.h>

#include <libintl.h>

#include <gtk--sig.h>
#include <gtk--/main.h>
#include <gtk--/window.h>

#include <corps/exception.hh>

#include "client.hh"
#include "gui.hh"
#include "gui_gamewindow.hh"
#include "gui_playfield.hh"


GUI_GameWindow::GUI_GameWindow(GUI_Playfield &pf) throw() :
  is_connecting(false),

  file_menu_item(gettext("File")),
  new_menu_item(gettext("New game")),
  open_menu_item(gettext("Open...")),
  connect_menu_item(gettext("Connect...")),
  leave_menu_item(gettext("Leave")),
  close_menu_item(gettext("Close")),
  exit_menu_item(gettext("Exit")),
  help_menu_item(gettext("Help")),
  about_menu_item(gettext("About...")),

  playfield(pf)
{
  set_title("GCORPS " VERSION);
  add(&main_box);
  main_box.show();

  // create menu
  main_box.pack_start(menu_bar, false, false, 0);
  menu_bar.show();

  // File/New game
  connect_to_method(new_menu_item.activate, this, &GUI_GameWindow::new_window);
  file_menu.append(new_menu_item);
  new_menu_item.show();
  // File/Open...
  connect_to_method(open_menu_item.activate, this, &GUI_GameWindow::open_game);
  file_menu.append(open_menu_item);
  open_menu_item.show();
  // File/Connect...
  connect_to_method(connect_menu_item.activate, this, &GUI_GameWindow::connect_to_game);
  file_menu.append(connect_menu_item);
  connect_menu_item.show();
  // File/Leave
  connect_to_method(leave_menu_item.activate, this, &GUI_GameWindow::leave_game);
  file_menu.append(leave_menu_item);
  leave_menu_item.show();
  leave_menu_item.set_sensitive(false);
  // File/---
  file_menu.append(separator_item1);
  separator_item1.show();
  // File/Close
  connect_to_method(close_menu_item.activate, this, &GUI_GameWindow::close);
  file_menu.append(close_menu_item);
  close_menu_item.show();
  // File/Exit
  connect_to_method(exit_menu_item.activate, this, &GUI_GameWindow::exit);
  file_menu.append(exit_menu_item);
  exit_menu_item.show();
  // File
  file_menu_item.set_submenu(file_menu);
  menu_bar.append(file_menu_item);
  file_menu_item.show();

  // Help/About...
  connect_to_method(about_menu_item.activate, this, &GUI_GameWindow::about);
  help_menu.append(about_menu_item);
  about_menu_item.show();
  // Help
  help_menu_item.set_submenu(help_menu);
  menu_bar.append(help_menu_item);
  help_menu_item.right_justify();
  help_menu_item.show();

  // playfield widget
  main_box.pack_start(playfield);
  playfield.show();
}


void GUI_GameWindow::connecting(bool yes) throw()
{
  is_connecting = yes;
  open_menu_item.set_sensitive(!yes);
  connect_menu_item.set_sensitive(!yes);
}

void GUI_GameWindow::connected(bool yes) throw()
{
  leave_menu_item.set_sensitive(yes);
}


void GUI_GameWindow::new_window() throw()
{
  try { new Client; }
  catch(Exception e) { GUI::exception(e); }
}

void GUI_GameWindow::open_game() throw()
{ open(); }

void GUI_GameWindow::connect_to_game() throw()
{ connect(); }

void GUI_GameWindow::leave_game() throw()
{ leave(); }

void GUI_GameWindow::close() throw()
{ delete_client(); }

void GUI_GameWindow::exit() throw()
{
  Gtk_Main::instance()->quit();
}


void GUI_GameWindow::about() throw()
{
  GUI::about();
}


gint GUI_GameWindow::delete_event_impl(GdkEventAny *) throw()
{
  delete_client();

  return 1;
}
