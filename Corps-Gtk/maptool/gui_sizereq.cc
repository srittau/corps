/*  Size Requester for CORPS MapTool
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

#include <libintl.h>

#include <corps/exception.hh>
#include <corps/tools.hh>

#include "gui.hh"
#include "gui_sizereq.hh"


//FIXME: disallow non-numeric characters
GUI_SizeRequester::GUI_SizeRequester(MapWidget::Size s) throw() :
  GUI_Requester(gettext("Choose New Size"), LAY_OKCANCEL),

  main_table(2, 2),
  x_label(gettext("Width:")),
  x_entry(),
  y_label(gettext("Height:")),
  y_entry()
{
  vbox_.pack_start(main_table);
  main_table.show();
  main_table.attach(x_label, 0, 1, 0, 1);
  x_label.show();
  main_table.attach(x_entry, 1, 2, 0, 1);
  x_entry.set_max_length(4);
  x_entry.set_text(num2str(s.width));
  x_entry.grab_focus();
  x_entry.show();

  main_table.attach(y_label, 0, 1, 1, 2);
  y_label.show();
  main_table.attach(y_entry, 1, 2, 1, 2);
  y_entry.set_max_length(4);
  y_entry.set_text(num2str(s.height));
  y_entry.show();

  ok_button.grab_default();
}


MapWidget::Size GUI_SizeRequester::get_size() throw()
{
  MapWidget::Size s;
  s.width  = strtoul(x_entry.get_text().c_str(), 0, 10);
  s.height = strtoul(y_entry.get_text().c_str(), 0, 10);
  return s;
}


// check if requester was filled out correctly, print an error if not,
// call super class if so
void GUI_SizeRequester::ok_pressed() throw()
{
  char *endptr;
  MapWidget::Size s;
  string text;

  text = x_entry.get_text();
  s.width  = strtoul(text.c_str(), &endptr, 10);
  if(text.empty() || *endptr != '\0')
    {
      GUI::exception(Exception(gettext("Invalid size")));
      return;
    }

  text = y_entry.get_text();
  s.height = strtoul(text.c_str(), &endptr, 10);
  if(text.empty() || *endptr != '\0')
    {
      GUI::exception(Exception(gettext("Invalid size")));
      return;
    }

  // check if size is in valid range
  if(s.width < 1 || s.height < 1 || s.width > 100 || s.height > 100)
    {
      GUI::exception(Exception(gettext("Invalid size")));
      return;
    }

  GUI_Requester::ok_pressed();
}
