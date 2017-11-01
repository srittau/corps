#ifndef GUI_MAPWIDGET_HH
#define GUI_MAPWIDGET_HH

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

#include <cstdio> //FIXME

#include "map_widget.hh"

class Map;


class GUI_MapWidget : public MapWidget
{
public:
  GUI_MapWidget() throw();
  GUI_MapWidget(const Map &m) throw();

protected:
  //FIXME
  virtual void drag_data_get_impl(GdkDragContext* p1, GtkSelectionData* p2, guint p3, guint32 p4) { printf("drag1\n"); }
  virtual void drag_data_delete_impl(GdkDragContext* p1) { printf("drag2\n"); }
  virtual void drag_leave_impl(GdkDragContext* p1, guint p2) { printf("drag3\n"); }
  virtual gboolean drag_motion_impl(GdkDragContext* p1, gint p2, gint p3, guint p4) { printf("drag4\n"); }
  virtual gboolean drag_drop_impl(GdkDragContext* p1, gint p2, gint p3, guint p4) { printf("drag5\n"); }
  virtual void drag_data_received_impl(GdkDragContext* p1, gint p2, gint p3, GtkSelectionData* p4, guint p5, guint32 p6) { printf("drag6\n"); }

private:
  void setup() throw();
};

#endif // GUI_MAPWIDGET_HH
