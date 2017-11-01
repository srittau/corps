/*  GUI_Playfield class implementation
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

#include <libintl.h>

#include <corps/game-wrapper.hh>

#include "gui_playfield.hh"


GUI_Playfield::GUI_Playfield() throw() :
  info_table(2, 2),
  name_label(gettext("Name:")),
  system_label(gettext("System:")),

  text_widget()
{
  set_border_width(5);

  pack_start(upper_box);
  upper_box.show();
  pack_start(text_box);
  text_box.show();

  upper_box.pack_start(stat_box);
  stat_box.show();
  upper_box.pack_start(main_sep, false, false, 0);
  main_sep.show();
  upper_box.pack_start(pf_box);
  pf_box.show();

  stat_box.pack_start(info_table);
  info_table.show();
  info_table.attach(name_label, 0, 1, 0, 1, GTK_FILL, 0);
  name_label.set_alignment(0.0, 0.5);
  name_label.show();
  info_table.attach(name_widget, 1, 2, 0, 1, GTK_FILL, 0);
  name_widget.show();
  info_table.attach(system_label, 0, 1, 1, 2, GTK_FILL, 0);
  system_label.set_alignment(0.0, 0.5);
  system_label.show();
  info_table.attach(system_widget, 1, 2, 1, 2, GTK_FILL, 0);
  system_widget.show();

  text_box.pack_start(text_widget);
  text_widget.set_editable(false);
  text_widget.set_word_wrap(true);
  text_widget.show();

  text_box.pack_start(entry_widget, false, false, 0);
  entry_widget.set_editable(true);
  entry_widget.grab_focus();
  connect_to_method(entry_widget.activate, this, &GUI_Playfield::entry_pressed);
  entry_widget.set_sensitive(false);
  entry_widget.show();
}


void GUI_Playfield::connect(const Game_Wrapper &game) throw()
{
  name_widget.set_text(game.get_name());
  system_widget.set_text(game.get_system().get_name());
#if 0 //FIXME
  if(game.has_text_handler())
    entry_widget.set_sensitive(true);
#endif
}


void GUI_Playfield::leave() throw()
{
  name_widget.set_text("");
  system_widget.set_text("");
  entry_widget.set_text("");
  entry_widget.set_sensitive(false);
  //FIXME: erase text_widget
}


void GUI_Playfield::print_text(const string &text) throw()
{
  string t = text;

  // double newlines
  string::size_type pos = 0;
  while((pos = t.find('\n', pos)) != string::npos)
    {
      t.insert(pos, 1, '\n');
      pos += 2;
    }

  // append final newlines
  t += "\n\n";

  // finally insert text into gadget
  text_widget.insert(0, 0, 0, t, t.size());
}


void GUI_Playfield::entry_pressed() throw()
{
  text_entered(entry_widget.get_text());
  entry_widget.set_text("");
}
