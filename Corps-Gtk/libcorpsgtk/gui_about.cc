/*  gtk+ about window for corps-gtk
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

#include <libintl.h>

#include "gui_about.hh"
#include "about.h"



//FIXME: text
GUI_About::GUI_About(const string &title, const string &text) throw() :
  picture(GTK_PREVIEW_COLOR),
  ok_button(gettext("Ok"))
{
  set_title(title);

  vbox_.set_border_width(10);

  // set up picture
  picture.size(about_width, about_height);
  guchar *dest;
  guchar *tmp = new guchar[about_width * 3];
  guchar *src = (guchar *)about_data;
  for(unsigned int y = 0; y < about_height; y++)
    {
      dest = tmp;
      for(unsigned int x = 0; x < about_width; x++)
	{
	  HEADER_PIXEL(src, dest);
	  dest += 3;
	}
      picture.draw_row(tmp, 0, y, about_width);
    }
  delete tmp;
  vbox_.pack_start(picture);
  picture.show();

  ok_button.set_flags(GTK_CAN_DEFAULT);
  connect_to_method(ok_button.clicked, this, &GUI_About::delete_self);
  action_area_.pack_start(ok_button);
  ok_button.grab_default();
  ok_button.show();
}


gint GUI_About::delete_event_impl(GdkEventAny *) throw()
{
  delete_self();

  return 1;
}
