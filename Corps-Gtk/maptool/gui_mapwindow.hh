#ifndef GUI_MAPWINDOW_HH
#define GUI_MAPWINDOW_HH

/*  MapWindow for MapTool
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

#include <gtk--/box.h>
#include <gtk--/clist.h>
#include <gtk--/menu.h>
#include <gtk--/menubar.h>
#include <gtk--/menuitem.h>
#include <gtk--/paned.h>
#include <gtk--/scrolledwindow.h>
#include <gtk--/statusbar.h>
#include <gtk--/window.h>

#include "gui_iconview.hh"
#include "gui_mapwidget.hh"

class File_Exception;
class Gtk_FileSelection;
class Map;


class GUI_MapWindow : public Gtk_Window, public virtual Gtk_Signal_Base
{
public:
  GUI_MapWindow() throw(File_Exception);
  GUI_MapWindow(const Map &map) throw();
  ~GUI_MapWindow() throw();

  void display_map(const Map &map) throw();

protected:
  virtual gint delete_event_impl(GdkEventAny *) throw();
  virtual void delete_self() throw();

private:
  static unsigned int open_cnt;

  // constructor support
  void setup() throw();

  // menu actions
  void new_window() throw();
  void open_map() throw();
  void open_new_map() throw();
  void close() throw();
  void exit() throw();
  void changesize() throw();
  void about() throw();

  // menu followup functions
  void map_chosen() throw();
  void new_map_chosen() throw();
  void close_file_req() throw();

  // threaded methods
  void do_changesize() throw();
  static void *try_changesize(void *o) throw();

  // map icon operations
  void init_icons(const MapSet &ms) throw();
  void set_field_name(string text) throw();
  void clear_field_name() throw();
  guint field_context_id;
  void set_mod_name(string text) throw();
  void clear_mod_name() throw();
  guint mod_context_id;

  // widgets
  Gtk_VBox main_box;
  Gtk_HBox body_box;
  Gtk_ScrolledWindow field_list_win;
  GUI_Iconview       field_list_widget;
  Gtk_ScrolledWindow mod_list_win;
  GUI_Iconview       mod_list_widget;

  Gtk_ScrolledWindow map_win;
  GUI_MapWidget      map_widget;

  Gtk_Statusbar status_bar;

  // menu widgets
  Gtk_MenuBar menu_bar;
  Gtk_Menu file_menu;
  Gtk_MenuItem file_menu_item;
  Gtk_MenuItem new_menu_item;
  Gtk_MenuItem open_menu_item;
  Gtk_MenuItem open_new_menu_item;
  Gtk_MenuItem separator_item1;
  Gtk_MenuItem close_menu_item;
  Gtk_MenuItem exit_menu_item;
  Gtk_Menu edit_menu;
  Gtk_MenuItem edit_menu_item;
  Gtk_MenuItem changesize_menu_item;
  Gtk_Menu help_menu;
  Gtk_MenuItem help_menu_item;
  Gtk_MenuItem about_menu_item;

  // temporary widgets
  Gtk_FileSelection *file_req;
};

#endif GUI_MAPWINDOW_HH
