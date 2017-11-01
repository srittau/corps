/*  gtk+ requester class for corps-gtk
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

#include "gui_requester.hh"


GUI_Requester::GUI_Requester(const string &title, ButtonLayout layout) throw() :
  self_destructing(false),

  ok_button(gettext("Ok")),
  cancel_button(gettext("Cancel"))
{
  pthread_mutex_init(&wait_mutex, 0);
  pthread_cond_init(&wait_cond, 0);

  set_title(title);

  vbox_.set_border_width(10);

  if(layout == LAY_OK || layout == LAY_OKCANCEL)
    {
      ok_button.set_flags(GTK_CAN_DEFAULT);
      connect_to_method(ok_button.clicked, this, &GUI_Requester::ok_pressed);
      action_area_.pack_start(ok_button);
      ok_button.show();
    }

  if(layout == LAY_OKCANCEL || layout == LAY_CANCEL)
    {
      cancel_button.set_flags(GTK_CAN_DEFAULT);
      connect_to_method(cancel_button.clicked, this, &GUI_Requester::cancel_pressed);
      action_area_.pack_end(cancel_button);
      cancel_button.show();
    }
}


GUI_Requester::~GUI_Requester() throw()
{
  pthread_cond_destroy(&wait_cond);
  pthread_mutex_destroy(&wait_mutex);
}


void GUI_Requester::handle_self_destruction() throw()
{
  self_destructing = true;
}


GUI_Requester::Action GUI_Requester::wait_for_action() throw()
{
  pthread_mutex_lock(&wait_mutex);
  pthread_cond_wait(&wait_cond, &wait_mutex);
  Action stat = status;
  pthread_mutex_unlock(&wait_mutex);

  return stat;
}


gint GUI_Requester::delete_event_impl(GdkEventAny *) throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_DESTROY;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();

  return 1;
}


void GUI_Requester::ok_pressed() throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_OK;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();
}


void GUI_Requester::cancel_pressed() throw()
{
  pthread_mutex_lock(&wait_mutex);
  status = ACTION_CANCEL;
  pthread_cond_broadcast(&wait_cond);
  pthread_mutex_unlock(&wait_mutex);

  if(self_destructing)
    delete_self();
}
