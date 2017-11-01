/*  Gtk+ message requesters for corps-gtk
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

#include "gui_msgreqs.hh"


//FIXME: reflow header and body
GUI_MessageRequester::GUI_MessageRequester(const string &title,
					   const string &header,
					   const string &body) throw() :
  GUI_Requester(title, LAY_OK),

  header_widget(header),
  body_widget(body)
{
  ok_button.grab_default();

  vbox_.pack_start(header_widget);
  header_widget.show();

  vbox_.pack_start(frame_widget);
  frame_widget.set_shadow_type(GTK_SHADOW_IN);
  frame_widget.show();
  frame_widget.add(&body_widget);
  body_widget.show();
}


//FIXME: reflow body
GUI_MessageRequester::GUI_MessageRequester(const string &title,
					   const string &body) throw() :
  GUI_Requester(title, LAY_OK),

  body_widget(body)
{
  ok_button.grab_default();

  vbox_.pack_start(frame_widget);
  frame_widget.set_shadow_type(GTK_SHADOW_IN);
  frame_widget.show();
  frame_widget.add(&body_widget);
  body_widget.show();
}
