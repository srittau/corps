#ifndef GUI_ICONVIEW_HH
#define GUI_ICONVIEW_HH

/*  Iconview GUI class for CORPS maptool
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

#include <string>

#include <gtk/gtkselection.h>
#include <gdk--/extra/imlib.h>
#include <gtk--/widget.h>


class GUI_Iconview : public Gtk_Widget
{
public:
  typedef struct { Gdk_Imlib::Image im; string text; } ListEntry;
  typedef vector<ListEntry> List;

  GUI_Iconview() throw();
  GUI_Iconview(const List &l) throw();
  virtual ~GUI_Iconview() throw() {}

  void set_list(const List &l) throw();

  Signal1<string> icon_name_set;
  Signal0         icon_name_cleared;

  static gchar dnd_target_string[];
  static guint dnd_target_info;
  static GtkTargetEntry dnd_target[];

protected:
  virtual void realize_impl() throw();
  virtual void size_request_impl(GtkRequisition *gr) throw();
  virtual gint expose_event_impl(GdkEventExpose *gee) throw();
  virtual gint button_press_event_impl(GdkEventButton *geb) throw();
  virtual gint motion_notify_event_impl(GdkEventMotion *gem) throw();
  virtual gint leave_notify_event_impl(GdkEventCrossing *gec) throw();
  virtual void drag_begin_impl(GdkDragContext *gdc) throw();
  virtual void drag_end_impl(GdkDragContext *gdc) throw();

  //FIXME
  virtual void drag_data_get_impl(GdkDragContext* p1, GtkSelectionData* p2, guint p3, guint32 p4) { printf("drag3\n"); }
  virtual void drag_data_delete_impl(GdkDragContext* p1) { printf("drag4\n"); }
  virtual void drag_leave_impl(GdkDragContext* p1, guint p2) { printf("drag5\n"); }
  virtual gboolean drag_motion_impl(GdkDragContext* p1, gint p2, gint p3, guint p4) { printf("drag6\n"); }
  virtual gboolean drag_drop_impl(GdkDragContext* p1, gint p2, gint p3, guint p4) { printf("drag7\n"); }
  virtual void drag_data_received_impl(GdkDragContext* p1, gint p2, gint p3, GtkSelectionData* p4, guint p5, guint32 p6) { printf("drag8\n"); }

private:
  void draw_it() throw();

  int icon_hit(gdouble x, gdouble y) throw();
  int last_hit;

  List list;

  gint16 w;
  gint16 h;
};

#endif // GUI_ICONVIEW_HH
