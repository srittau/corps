#ifndef GUI_BUSYREQ_HH
#define GUI_BUSYREQ_HH

/*  Gtk+ busy requester for corps-gtk
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

#include <gtk--/label.h>

#include "gui_requester.hh"


class GUI_BusyRequester : public GUI_Requester
{
public:
  class Notify { public: virtual void notify() = 0; };

  GUI_BusyRequester(const string &title, const string &text) throw();

  // WARNING: should only be set, while window is NOT shown - possible
  // race-condition with cancel_pressed()
  void set_oncancel(Notify &o) throw() { notifier = &o; }
  void set_oncancel() throw() { notifier = 0; }

private:
  virtual void cancel_pressed() throw();

private:
  Gtk_Label header_widget;

  Notify *notifier;
};

#endif // GUI_BUSYREQ_HH
