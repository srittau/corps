#ifndef GUI_EXCEPTION_HH
#define GUI_EXCEPTION_HH

/*  Class for handling an exception inside of a gtk+ window
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

#include <gtk--/button.h>
#include <gtk--/dialog.h>
#include <gtk--/frame.h>
#include <gtk--/label.h>

class Exception;


class GUI_Exception : public Gtk_Dialog {
public:
  GUI_Exception(const Exception &e) throw();

  virtual void delete_self() throw() { Gtk_Dialog::delete_self(); };

protected:
  virtual gint delete_event_impl(GdkEventAny *) throw();

private:
  Gtk_Frame error_frame;
  Gtk_Label error_field;
  Gtk_Button ok_button;
};

#endif // GUI_EXCEPTION_HH
