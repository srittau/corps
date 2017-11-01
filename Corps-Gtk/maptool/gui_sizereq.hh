#ifndef GUI_SIZEREQ_HH
#define GUI_SIZEREQ_HH

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

#include <gtk--/entry.h>
#include <gtk--/label.h>
#include <gtk--/table.h>

#include "map_widget.hh"

#include "gui_requester.hh"


class GUI_SizeRequester : public GUI_Requester
{
public:
  GUI_SizeRequester(MapWidget::Size s) throw();

  MapWidget::Size get_size() throw();

protected:
  virtual void ok_pressed() throw();

private:
  Gtk_Table main_table;
  Gtk_Label x_label;
  Gtk_Entry x_entry;
  Gtk_Label y_label;
  Gtk_Entry y_entry;
};

#endif // GUI_SIZEREQ_HH
