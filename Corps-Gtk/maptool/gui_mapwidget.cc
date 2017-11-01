/*  MapWidget class for MapTool
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

#include <gtk/gtkdnd.h> //FIXME

#include "gui_iconview.hh"
#include "gui_mapwidget.hh"


GUI_MapWidget::GUI_MapWidget() throw() :
  MapWidget()
{
  setup();
}


GUI_MapWidget::GUI_MapWidget(const Map &m) throw() :
  MapWidget(m)
{
  setup();
}


void GUI_MapWidget::setup() throw()
{
  set_events(get_events() |
	     GDK_POINTER_MOTION_MASK |
	     GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

  struct GtkTargetEntry te[] = { {
    GUI_Iconview::dnd_target_string,
    //FIXME    GTK_TARGET_SAME_APP,
    0,
    GUI_Iconview::dnd_target_info
  } };

  //FIXME  drag_dest_set(GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP, te, 1, GDK_ACTION_DEFAULT);
  printf("1\n"); //FIXME
  drag_dest_set(GTK_DEST_DEFAULT_ALL, te, 1, GDK_ACTION_DEFAULT);
}
