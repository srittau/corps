/*  Gtk+ input requesters for corps-gtk
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

#include "gui_inputreqs.hh"


//FIXME: automatically reflow text
GUI_StringRequester::GUI_StringRequester(const string &title,
					 const string &text,
					 ButtonLayout layout) throw() :
  GUI_Requester(title, layout),

  text_widget(text),
  text_entry()
{
  vbox_.pack_start(text_widget);
  text_widget.show();

  vbox_.pack_start(text_entry);
  text_entry.set_max_length(1024);
  text_entry.set_editable(true);
  connect_to_method(text_entry.activate, static_cast<GUI_Requester *>(this), &GUI_StringRequester::ok_pressed);
  text_entry.grab_focus();
  text_entry.show();

  ok_button.grab_default();
}


//FIXME: automatically reflow text
GUI_TextRequester::GUI_TextRequester(const string &title,
				     const string &text,
				     ButtonLayout layout) throw() :
  GUI_Requester(title, layout),

  text_widget(text),
  text_entry()
{
  vbox_.pack_start(text_widget);
  text_widget.show();
  vbox_.pack_start(text_entry);
  text_entry.set_editable(true);
  text_entry.grab_focus();
  text_entry.show();

  ok_button.grab_default();
}


string GUI_TextRequester::get_contents() const throw()
{
  return text_entry.get_chars(0, -1);
}
