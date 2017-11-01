/*  Gtk+ busy requester for corps-gtk
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

#include "gui_busyreq.hh"


//FIXME: reflow header
GUI_BusyRequester::GUI_BusyRequester(const string &title, const string &text) throw() :
  GUI_Requester(title, LAY_CANCEL),

  header_widget(text),

  notifier(0)
{
  vbox_.pack_start(header_widget);
  header_widget.show();

  cancel_button.grab_default();
}


void GUI_BusyRequester::cancel_pressed() throw()
{
  if(notifier)
    notifier->notify();
  GUI_Requester::cancel_pressed();
}
