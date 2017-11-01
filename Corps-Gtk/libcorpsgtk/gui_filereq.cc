/*  gtk+ file requester class for corps-gtk
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
#include <libintl.h>

#include "gui_filereq.hh"


GUI_FileRequester::GUI_FileRequester(const string &title) throw() :
  Gtk_FileSelection(title),
  self_destructing(false)
{
  pthread_mutex_init(&wait_mutex, 0);
  pthread_cond_init(&wait_cond, 0);

  connect_to_method(get_ok_button()->clicked, this, &GUI_FileRequester::ok_pressed);
  connect_to_method(get_cancel_button()->clicked, this, &GUI_FileRequester::cancel_pressed);
}


GUI_FileRequester::~GUI_FileRequester() throw()
{
  pthread_cond_destroy(&wait_cond);
  pthread_mutex_destroy(&wait_mutex);
}


void GUI_FileRequester::handle_self_destruction() throw()
{
  self_destructing = true;
}


GUI_FileRequester::Action GUI_FileRequester::wait_for_action() throw()
{
  pthread_mutex_lock(&wait_mutex);
  pthread_cond_wait(&wait_cond, &wait_mutex);
  Action stat = status;
  pthread_mutex_unlock(&wait_mutex);

  return stat;
}


gint GUI_FileRequester::delete_event_impl(GdkEventAny *) throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_DESTROY;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();

  return 1;
}


void GUI_FileRequester::ok_pressed() throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_OK;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();
}


void GUI_FileRequester::cancel_pressed() throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_CANCEL;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();
}
