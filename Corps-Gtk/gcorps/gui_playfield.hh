#ifndef GUI_PLAYFIELD_HH
#define GUI_PLAYFIELD_HH

/*  Interface for gui_playfield.cc
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

#include <gtk--sig.h>
#include <gtk--/box.h>
#include <gtk--/entry.h>
#include <gtk--/label.h>
#include <gtk--/separator.h>
#include <gtk--/table.h>
#include <gtk--/text.h>


class Game_Wrapper;


class GUI_Playfield : public Gtk_VBox
{
public:
  GUI_Playfield() throw();

  void connect(const Game_Wrapper &game) throw();
  // it is save to call leave() even if we are not currently connected
  void leave() throw();

  void print_text(const string &text) throw();

  Signal1<string> text_entered;

private:
  void entry_pressed() throw();

  Gtk_HBox upper_box;
  Gtk_VBox stat_box;
  Gtk_VBox pf_box;
  Gtk_VBox text_box;
  Gtk_VSeparator main_sep;

  Gtk_Table info_table;
  Gtk_Label name_label;
  Gtk_Label name_widget;
  Gtk_Label system_label;
  Gtk_Label system_widget;

  Gtk_Text text_widget;
  Gtk_Entry entry_widget;
};

#endif // GUI_PLAYFIELD_HH
