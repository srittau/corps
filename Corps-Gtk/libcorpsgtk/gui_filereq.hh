#ifndef GUI_FILEREQ_HH
#define GUI_FILEREQ_HH

/*  Gtk+ file requester class for corps-gtk
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

#include <string>

#include <pthread.h>

#include <gtk--/fileselection.h>


class Exception;


class GUI_FileRequester : public Gtk_FileSelection {
public:
  enum Action { ACTION_OK, ACTION_CANCEL, ACTION_DESTROY };

  GUI_FileRequester(const string &title) throw();
  virtual ~GUI_FileRequester() throw();

  // use this only if object was initialized with "new"
  void handle_self_destruction() throw();
  Action wait_for_action() throw();

protected:
  virtual gint delete_event_impl(GdkEventAny *) throw();

  virtual void ok_pressed() throw();
  virtual void cancel_pressed() throw();

private:
  Action status;
  pthread_mutex_t wait_mutex;
  pthread_cond_t wait_cond;

  bool self_destructing;
};

#endif // GUI_FILEREQ_HH
