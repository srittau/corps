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

#include <corps/mapset.hh>

#include "gui_iconview.hh"


#define BORDER_X 5
#define BORDER_Y 5


gchar GUI_Iconview::dnd_target_string[] = "ICON";
guint GUI_Iconview::dnd_target_info = 1;
GtkTargetEntry GUI_Iconview::dnd_target[] = { { dnd_target_string, 0, dnd_target_info } };


GUI_Iconview::GUI_Iconview() throw() :
  Gtk_Widget(),
  last_hit(-1),
  list(),
  w(0),
  h(0)
{
}


GUI_Iconview::GUI_Iconview(const List &l) throw() :
  Gtk_Widget(),
  last_hit(-1),
  list(l),
  w(0),
  h(0)
{
}


void GUI_Iconview::set_list(const List &l) throw()
{
  list = l;

  // calculate ideal widget size
  w = 0;
  h = BORDER_Y;
  List::size_type pos = 0;
  while(pos < list.size())
    {
      const Gdk_Imlib::Image &im = list[pos].im;
      if(im.rgb_width() > w) w = im.rgb_width();
      h += im.rgb_height() + BORDER_Y;
      pos++;
    }
  w += BORDER_X * 2;

  if(is_realized())
    draw_it();
}


void GUI_Iconview::realize_impl() throw()
{
  Gdk_WindowAttr attributes;

  attributes->x = 0;
  attributes->y = 0;
  attributes->width = width();
  attributes->height = height();
  attributes->wclass = GDK_INPUT_OUTPUT;
  attributes->window_type = GDK_WINDOW_CHILD;
  attributes->event_mask = get_events() | 
    GDK_POINTER_MOTION_MASK | GDK_LEAVE_NOTIFY_MASK |
    GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK;
  attributes->visual = get_visual();
  attributes->colormap = get_colormap();

  gint attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
  Gdk_Window window(get_parent_window(), attributes, attributes_mask);
  gtkobj()->window = window.gdkobj(); //FIXME: c++ function
  window.set_user_data(gtkobj());

  get_style()->attach(window);
  get_style()->set_background(window, GTK_STATE_NORMAL);

  GTK_WIDGET_SET_FLAGS (gtkobj(), GTK_REALIZED); //FIXME: c++ function
}


void GUI_Iconview::size_request_impl(GtkRequisition *gr) throw()
{
  gr->width  = w;
  gr->height = h;
}


gint GUI_Iconview::expose_event_impl(GdkEventExpose *gee) throw()
{
  draw_it();
  return FALSE; //FIXME: ?
}


gint GUI_Iconview::button_press_event_impl(GdkEventButton *geb) throw()
{
  if(geb->button != 1 || geb->type != GDK_BUTTON_PRESS)
    return FALSE; //FIXME: ?

  int hit = icon_hit(geb->x, geb->y);
  if(hit < 0)
    return FALSE; //FIXME: ?

  if(hit != last_hit)
    {
      // if we have already set an icon name, clear it first
      if(last_hit >= 0)
	icon_name_cleared();

      icon_name_set(list[hit].text);
      last_hit = hit;
    }

  GtkTargetList *l = gtk_target_list_new(dnd_target, 1); //FIXME: c++ function
  //FIXME  drag_begin(l, GDK_ACTION_DEFAULT, 1, (GdkEvent *)geb);

  return FALSE; //FIXME: ?
}


gint GUI_Iconview::motion_notify_event_impl(GdkEventMotion *gem) throw()
{
  int hit = icon_hit(gem->x, gem->y);

  if(hit != last_hit)
    {
      // if we have already set an icon name, clear it first
      if(last_hit >= 0)
	icon_name_cleared();

      if(hit >= 0)
	icon_name_set(list[hit].text);

      last_hit = hit;
    }

  return FALSE; //FIXME: ?
}


gint GUI_Iconview::leave_notify_event_impl(GdkEventCrossing *gec) throw()
{
  if(last_hit >= 0)
    {
      icon_name_cleared();
      last_hit = -1;
    }

  return FALSE; //FIXME: ?
}


//FIXME #include <cstdio> //FIXME
#include <gtk/gtkdnd.h> //FIXME
void GUI_Iconview::drag_begin_impl(GdkDragContext *gdc) throw()
{
  Gdk_DragContext ctx(gdc);
  Gdk_Imlib::Image im = list[last_hit].im;
  Gdk_Colormap colormap = get_colormap();
  im.render(im.rgb_width(), im.rgb_height());
  Gdk_Pixmap pixmap(im.copy_image());
  Gdk_Bitmap mask(im.copy_mask());

#if 0 //FIXME
  printf("1\n"); //FIXME
  drag_set_icon_pixmap(ctx,
		       colormap, pixmap, mask,
		       0, 0);
  printf("2\n"); //FIXME
#endif
  gtk_drag_set_icon_pixmap(gdc,
			   colormap.gdkobj(), pixmap.gdkobj(), mask.gdkobj(),
			   0, 0);
}


void GUI_Iconview::drag_end_impl(GdkDragContext *gdc) throw()
{
  if(last_hit >= 0)
    {
      icon_name_cleared();
      last_hit = -1;
    }
}


void GUI_Iconview::draw_it() throw()
{
  unsigned int pos = 0;
  while(pos < list.size())
    {
      const Gdk_Imlib::Image &im = list[pos].im;
      Gdk_Window win = get_window();
      im.paste(win,
	       BORDER_X, (im.rgb_height() + BORDER_Y) * pos + BORDER_Y,
	       im.rgb_width(), im.rgb_height());
      pos++;
    }
}


int GUI_Iconview::icon_hit(gdouble dx, gdouble dy) throw()
{
  guint x = static_cast<guint>(dx);
  guint y = static_cast<guint>(dy);

  if(x < BORDER_X || y < BORDER_Y)
    return -1;

  x -= BORDER_X;
  y -= BORDER_Y;

  List::size_type pos = 0;
  while(pos < list.size())
    {
      const Gdk_Imlib::Image &im = list[pos].im;
      if(y < im.rgb_height() + BORDER_Y)
	{
	  if(x >= im.rgb_width())
	    return -1;
	  if(y >= im.rgb_height())
	    return -1;
	  return pos;
	}
      y -= im.rgb_height() + BORDER_Y;
      pos++;
    }

  return -1;
}
