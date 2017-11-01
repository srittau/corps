#ifndef GUI_GAMECHOOSER_HH
#define GUI_GAMECHOOSER_HH

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

#include <gdk--/bitmap.h>
#include <gdk--/pixmap.h>
#include <gtk--/clist.h>

#include <corps/game-wrapper.hh>

#include "gui_requester.hh"


class Client_GUI;


class GUI_GameChooser : public GUI_Requester {
public:
  GUI_GameChooser(const GameList &l) throw();
  virtual ~GUI_GameChooser() throw() {};

  Game_Wrapper get_contents() const throw();

protected:
  virtual void realize_impl() throw();

private:
  GameList list;

  void insert_row(gint row, const Game_Wrapper &info) throw();

  void sort_by_column(gint col) throw();
  void row_selected(gint row, gint column, GdkEvent *) throw();
  gint current_row;

  Gtk_CList list_widget;

  Gdk_Pixmap multip_pixmap;
  Gdk_Bitmap multip_mask;
  Gdk_Pixmap multic_pixmap;
  Gdk_Bitmap multic_mask;
  Gdk_Pixmap lamp_pixmap;
  Gdk_Bitmap lamp_mask;
};

#endif // GUI_GAMELIST_HH
