/*  MapWidget class
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

#include <gtk--/pixmap.h>

#include <corps/exception.hh>
#include <corps/map.hh>

#include "gui_exception.hh"
#include "map_widget.hh"


MapWidget::MapWidget() throw() :
  Gtk_DrawingArea(),

  map(),

  pixmap(),
  width(0),
  height(0)
{
  //FIXME: empty pixmap
}


MapWidget::MapWidget(const Map &m) throw() :
  Gtk_DrawingArea(),

  map(m),

  pixmap(),
  width(0),
  height(0)
{
  recalc_widget();
}


void MapWidget::set_map(const Map &m) throw()
{
  map = m;
  recalc_widget();
}


MapWidget_Size MapWidget::get_size() throw()
{
  Size s;
  s.width = map.get_width();
  s.height = map.get_height();
  return s;
}


void MapWidget::set_size(Size s) throw()
{
  map.resize(s);
  recalc_widget();
}


void MapWidget::size_request_impl(GtkRequisition *gr) throw()
{
  gr->width  = width;
  gr->height = height;
}


gint MapWidget::map_event_impl(GdkEventAny *gea) throw()
{
  pixmap = Gdk_Pixmap(get_window(), width, height, -1);
  map.construct_map(pixmap);

  return FALSE; //FIXME: ?
}


gint MapWidget::expose_event_impl(GdkEventExpose *gee) throw()
{
  Gdk_GC gc(get_style()->gtkobj()->fg_gc[GTK_WIDGET_STATE(GTK_WIDGET(gtkobj()))]);
  get_window().draw_pixmap(gc, pixmap,
			   gee->area.x, gee->area.y,
			   gee->area.x, gee->area.y,
			   gee->area.width, gee->area.height);
  return FALSE; //FIXME: ?
}


void MapWidget::recalc_widget() throw()
{
  const MapSet &ms = map.get_mapset();
  width  = map.get_width()  * ms.get_width();
  height = map.get_height() * ms.get_height();
  set_usize(width, height);

  if(is_mapped())
    {
      pixmap = Gdk_Pixmap(get_window(), width, height, -1);
      map.construct_map(pixmap);
    }
}
