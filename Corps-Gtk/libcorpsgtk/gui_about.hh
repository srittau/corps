#ifndef GUI_ABOUT_HH
#define GUI_ABOUT_HH

/*  Gtk+ about window for corps-gtk
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

#include <gtk--/button.h>
#include <gtk--/dialog.h>
#include <gtk--/preview.h>


class GUI_About : public Gtk_Dialog {
public:
  GUI_About(const string &title, const string &text) throw();

  virtual void delete_self() { Gtk_Dialog::delete_self(); };

protected:
  virtual gint delete_event_impl(GdkEventAny *) throw();

private:
  Gtk_Preview picture;
  Gtk_Button ok_button;
};

#endif // GUI_ABOUT_HH
