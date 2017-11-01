#ifndef MAP_WIDGET_HH
#define MAP_WIDGET_HH

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

#include <gtk--/drawingarea.h>

#include <corps/map.hh>

class MapSet;


class MapWidget : public Gtk_DrawingArea
{
public:
  typedef Map::Size Size;

  MapWidget() throw();
  MapWidget(const Map &m) throw();

  void set_map(const Map &m) throw();
  Size get_size() throw();
  void set_size(Size s) throw();

protected:
  virtual void size_request_impl(GtkRequisition *gr) throw();
  virtual gint map_event_impl(GdkEventAny *gea) throw();
  virtual gint expose_event_impl(GdkEventExpose *gee) throw();

private:
  void recalc_widget() throw();

  Map map;

  // backing pixmap
  Gdk_Pixmap pixmap;
  gint width;
  gint height;
};

typedef MapWidget::Size MapWidget_Size; // clutch to make it work with egcs

#endif // MAP_WIDGET_HH
