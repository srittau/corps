/*  MapWindow class for MapTool
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

#include <config.h>

#include <cstdlib>

#include <pthread.h>
#include <libintl.h>

#include <gtk--/fileselection.h>
#include <gtk--/main.h>

#include <corps/file_exception.hh>
#include <corps/mapfile.hh>
#include <corps/mapsetfile.hh>

#include "gui.hh"
#include "gui_exception.hh"
#include "gui_mapwindow.hh"
#include "gui_sizereq.hh"
#include "trashcan.hh"

extern GUI *gui;
extern Trashcan trash;


unsigned int GUI_MapWindow::open_cnt = 0;


GUI_MapWindow::GUI_MapWindow() throw(File_Exception) :
  main_box(),
  body_box(),
  field_list_win(),
  field_list_widget(),
  mod_list_win(),
  mod_list_widget(),

  map_win(),
  map_widget(),

  status_bar(),

  file_menu_item(gettext("File")),
  new_menu_item(gettext("New Window")),
  open_menu_item(gettext("Open...")),
  open_new_menu_item(gettext("Open new...")),
  close_menu_item(gettext("Close")),
  exit_menu_item(gettext("Exit")),
  edit_menu_item(gettext("Edit")),
  changesize_menu_item(gettext("Change Size...")),
  help_menu_item(gettext("Help")),
  about_menu_item(gettext("About...")),

  file_req(0)
{
  setup();
}


GUI_MapWindow::GUI_MapWindow(const Map &map) throw() :
  main_box(),
  body_box(),
  field_list_win(),
  field_list_widget(),
  mod_list_win(),
  mod_list_widget(),

  map_win(),
  map_widget(map),

  status_bar(),

  file_menu_item(gettext("File")),
  new_menu_item(gettext("New Window")),
  open_menu_item(gettext("Open...")),
  open_new_menu_item(gettext("Open new...")),
  close_menu_item(gettext("Close")),
  exit_menu_item(gettext("Exit")),
  edit_menu_item(gettext("Edit")),
  changesize_menu_item(gettext("Change Size...")),
  help_menu_item(gettext("Help")),
  about_menu_item(gettext("About...")),

  file_req(0)
{
  setup();

  init_icons(map.get_mapset());
}


GUI_MapWindow::~GUI_MapWindow() throw()
{
  close_file_req();
}


void GUI_MapWindow::display_map(const Map &map) throw()
{
  init_icons(map.get_mapset());
  map_widget.set_map(map);
}


void GUI_MapWindow::new_window() throw()
{
  try { gui->construct_map(); }
  catch(Exception e) { GUI::exception(e); }
}


void GUI_MapWindow::open_map() throw()
{
  if(file_req)
    return;

  open_menu_item.set_sensitive(false);
  file_req = new Gtk_FileSelection(gettext("Choose a map file"));
  connect_to_method(file_req->get_ok_button()->clicked, this, &GUI_MapWindow::map_chosen);
  connect_to_method(file_req->get_cancel_button()->clicked, this, &GUI_MapWindow::close_file_req);
  file_req->show();
}


void GUI_MapWindow::open_new_map() throw()
{
  if(file_req)
    return;

  open_menu_item.set_sensitive(false);
  file_req = new Gtk_FileSelection(gettext("Choose a map file"));
  connect_to_method(file_req->get_ok_button()->clicked, this, &GUI_MapWindow::new_map_chosen);
  connect_to_method(file_req->get_cancel_button()->clicked, this, &GUI_MapWindow::close_file_req);
  file_req->show();
}


void GUI_MapWindow::map_chosen() throw()
{
  try
    {
      string filename = file_req->get_filename();
      close_file_req();
      display_map(MapFile(filename));
    }
  catch(File_Exception e)
    {
      GUI_Exception *win = new GUI_Exception(e);
      win->show();
    }
}


void GUI_MapWindow::new_map_chosen() throw()
{
  string filename = file_req->get_filename();
  close_file_req();
  GUI_MapWindow *win = new GUI_MapWindow(MapFile(filename));
  win->show();
}


void GUI_MapWindow::close_file_req() throw()
{
  if(file_req)
    {
      file_req->hide();
      delete file_req;
      file_req = 0;
      open_menu_item.set_sensitive(true);
    }
}


void GUI_MapWindow::close() throw()
{
  delete_self();
}


void GUI_MapWindow::exit() throw()
{
  Gtk_Main::instance()->quit();
}


void GUI_MapWindow::changesize() throw()
{
  pthread_t thread;
  pthread_create(&thread, 0, &try_changesize, this);
  pthread_detach(thread);
}


void GUI_MapWindow::about() throw()
{
  gui->about();
}


gint GUI_MapWindow::delete_event_impl(GdkEventAny *) throw()
{
  delete_self();

  return 1;
}


void GUI_MapWindow::delete_self() throw()
{
  if(!--open_cnt)
    Gtk_Main::instance()->quit();
  else
    Gtk_Window::delete_self();
}


void GUI_MapWindow::init_icons(const MapSet &ms) throw()
{
  GUI_Iconview::List l;

  MapSet::FieldList fl = ms.get_field_list();
  MapSet::FieldList::size_type pos = 0;
  while(pos < fl.size())
    {
      GUI_Iconview::ListEntry e = { fl[pos].get_pixmap(), fl[pos].get_name() };
      l.insert(l.end(), e);
      pos++;
    }
  field_list_widget.set_list(l);

  l.clear();
  MapSet::ModifierList ml = ms.get_modifier_list();
  pos = 0;
  while(pos < ml.size())
    {
      GUI_Iconview::ListEntry e = { ml[pos].get_pixmap(), ml[pos].get_name() };
      l.insert(l.end(), e);
      pos++;
    }
  mod_list_widget.set_list(l);
}


void GUI_MapWindow::set_field_name(string text) throw()
{
  status_bar.push(field_context_id, text);
}


void GUI_MapWindow::clear_field_name() throw()
{
  status_bar.pop(field_context_id);
}


void GUI_MapWindow::set_mod_name(string text) throw()
{
  status_bar.push(mod_context_id, text);
}


void GUI_MapWindow::clear_mod_name() throw()
{
  status_bar.pop(mod_context_id);
}


void GUI_MapWindow::setup() throw()
{
  open_cnt++;

  field_context_id = status_bar.get_context_id("field");
  mod_context_id   = status_bar.get_context_id("mod");

  set_usize(600, 400);
  set_title("CORPS MapTool " VERSION);
  add(&main_box);
  main_box.show();

  // create menu
  main_box.pack_start(menu_bar, false, false, 0);
  menu_bar.show();

  // File/New game
  connect_to_method(new_menu_item.activate, this, &GUI_MapWindow::new_window);
  file_menu.append(new_menu_item);
  new_menu_item.show();
  // File/Open...
  connect_to_method(open_menu_item.activate, this, &GUI_MapWindow::open_map);
  file_menu.append(open_menu_item);
  open_menu_item.show();
  // File/Open new...
  connect_to_method(open_new_menu_item.activate, this, &GUI_MapWindow::open_new_map);
  file_menu.append(open_new_menu_item);
  open_new_menu_item.show();
  // File/---
  file_menu.append(separator_item1);
  separator_item1.show();
  // File/Close
  connect_to_method(close_menu_item.activate, this, &GUI_MapWindow::close);
  file_menu.append(close_menu_item);
  close_menu_item.show();
  // File/Exit
  connect_to_method(exit_menu_item.activate, this, &GUI_MapWindow::exit);
  file_menu.append(exit_menu_item);
  exit_menu_item.show();
  // File
  file_menu_item.set_submenu(file_menu);
  menu_bar.append(file_menu_item);
  file_menu_item.show();

  // Edit/Change Size...
  connect_to_method(changesize_menu_item.activate, this, &GUI_MapWindow::changesize);
  edit_menu.append(changesize_menu_item);
  changesize_menu_item.show();
  // Edit
  edit_menu_item.set_submenu(edit_menu);
  menu_bar.append(edit_menu_item);
  edit_menu_item.show();

  // Help/About...
  connect_to_method(about_menu_item.activate, this, &GUI_MapWindow::about);
  help_menu.append(about_menu_item);
  about_menu_item.show();
  // Help
  help_menu_item.set_submenu(help_menu);
  menu_bar.append(help_menu_item);
  help_menu_item.right_justify();
  help_menu_item.show();

  main_box.pack_start(body_box);
  body_box.show();

  // MapSet Handling Widgets
  body_box.pack_start(field_list_win, false, false, 0);
  field_list_win.set_policy(GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  field_list_win.show();
  field_list_win.add_with_viewport(field_list_widget);
  connect_to_method(field_list_widget.icon_name_set, this, &GUI_MapWindow::set_field_name);
  connect_to_method(field_list_widget.icon_name_cleared, this, &GUI_MapWindow::clear_field_name);
  field_list_widget.show();

  // Map Widget
  body_box.pack_start(map_win);
  map_win.set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  map_win.show();
  map_win.add_with_viewport(map_widget);
  map_widget.show();

  body_box.pack_start(mod_list_win, false, false, 0);
  mod_list_win.set_policy(GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  mod_list_win.show();
  mod_list_win.add_with_viewport(mod_list_widget);
  connect_to_method(mod_list_widget.icon_name_set, this, &GUI_MapWindow::set_mod_name);
  connect_to_method(mod_list_widget.icon_name_cleared, this, &GUI_MapWindow::clear_mod_name);
  mod_list_widget.show();

  // Status Bar
  main_box.pack_start(status_bar, false, false, 0);
  status_bar.show();
}


void GUI_MapWindow::do_changesize() throw()
{
  gui->lock();
  changesize_menu_item.set_sensitive(false);
  GUI_SizeRequester *req = new GUI_SizeRequester(map_widget.get_size());
  req->show();

  unsigned int n = gui->freelock();
  if(req->wait_for_action() == GUI_SizeRequester::ACTION_OK)
    {
      gui->relock(n);
      map_widget.set_size(req->get_size());
    }
  else
    gui->relock(n);

  req->hide();
  delete req;
  changesize_menu_item.set_sensitive(true);
  gui->unlock();
}


void *GUI_MapWindow::try_changesize(void *o) throw()
{
  static_cast<GUI_MapWindow *>(o)->do_changesize();
  return 0;
}
