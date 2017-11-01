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

#include <fstream>
#include <libintl.h>

#include <corps/exception.hh>

#include "gui_exception.hh"


GUI_Exception::GUI_Exception(const Exception &e) throw() :
  ok_button(gettext("Ok"))
{
    set_title(gettext("Error"));

    vbox_.set_border_width(10);
    vbox_.pack_start(error_frame);
    error_frame.set_shadow_type(GTK_SHADOW_IN);
    error_frame.show();

    error_field.set_text(e.get_error_string());
    error_frame.add(error_field);
    error_field.show();

    ok_button.set_flags(GTK_CAN_DEFAULT);
    connect_to_method(ok_button.clicked, this, &GUI_Exception::delete_self);
    action_area_.pack_start(ok_button);
    ok_button.grab_default();
    ok_button.show();
}


gint GUI_Exception::delete_event_impl(GdkEventAny *) throw()
{
    delete_self();

    return 1;
}
