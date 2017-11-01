/*  Game Choose Requester for GCorps
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

#include <libintl.h>

#include <gdk/gdk.h>
#include <gtk--/style.h>

#include "gui_gamechooser.hh"
#include "utils.hh"


#define LIST_COLUMNS 3


GUI_GameChooser::GUI_GameChooser(const GameList &l) throw() :
  GUI_Requester(gettext("Select a Game"), LAY_OKCANCEL),

  list(l),

  list_widget(LIST_COLUMNS),

  current_row(-1)
{
  ok_button.set_sensitive(false);

  list_widget.set_selection_mode(GTK_SELECTION_SINGLE);
  list_widget.set_column_title(0, gettext("Name"));
  list_widget.set_column_title(1, gettext("System"));
  list_widget.set_column_title(2, gettext("Flags"));
  list_widget.column_title_active(0);
  list_widget.column_title_active(1);
  list_widget.column_title_passive(2);
  list_widget.column_titles_show();
  connect_to_method(list_widget.select_row, this, &GUI_GameChooser::row_selected);
  connect_to_method(list_widget.click_column, this, &GUI_GameChooser::sort_by_column);
  vbox_.pack_start(list_widget);

  // fill list
  gint row = -1;
  while(++row < list.size())
    insert_row(row, list[row]);

  list_widget.show();

  //FIXME: return means ok
}


Game_Wrapper GUI_GameChooser::get_contents() const throw()
{
  return *static_cast<Game_Wrapper *>(list_widget.get_row_data(current_row));
}


void GUI_GameChooser::realize_impl() throw()
{
  GUI_Requester::realize_impl();

  //FIXME: error if pixmaps don't exist
  const Gdk_Color color(const_cast<GdkColor *>(&get_style()->gtkobj()->white));
  multip_pixmap.create_from_xpm(get_window(),
				multip_mask,
				color,
				PIXMAPDIR "/corps_multip.xpm");
  multic_pixmap.create_from_xpm(get_window(),
				multic_mask,
				color,
				PIXMAPDIR "/corps_multic.xpm");
  lamp_pixmap.create_from_xpm(get_window(),
			      lamp_mask,
			      color,
			      PIXMAPDIR "/corps_lamp.xpm");
}


void GUI_GameChooser::insert_row(gint row, const Game_Wrapper &info) throw()
{
  if(!is_realized())
    realize();

  const gchar *text[LIST_COLUMNS];
  for(unsigned int x = 0; x < LIST_COLUMNS; x++)
    text[x] = "";

  list_widget.insert_row(row, text);
  list_widget.set_text(row, 0, info.get_name().c_str());
  list_widget.set_text(row, 1, info.get_system().get_name().c_str());

  //FIXME: multiple flags
#if 0 //FIXME
  if(info.is_mastered())
    list_widget.set_pixmap(row, 2, lamp_pixmap, lamp_mask);
  else if(info.is_multi_character())
    list_widget.set_pixmap(row, 2, multic_pixmap, multic_mask);
  else if(info.is_multi_player())
    list_widget.set_pixmap(row, 2, multip_pixmap, multip_mask);
#endif

  list_widget.set_row_data(row, &const_cast<Game_Wrapper &>(info));
}


void GUI_GameChooser::sort_by_column(gint col) throw()
{
  //FIXME
}


void GUI_GameChooser::row_selected(gint row, gint col, GdkEvent *) throw()
{
  current_row = row;
  ok_button.set_sensitive(true);
  ok_button.grab_default();
}
