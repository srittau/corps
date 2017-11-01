/*  GUI handling class (GTK-- version)
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

#include <config.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>
#include <libintl.h>

#include <gdk_imlib.h>

#include <corps/file_exception.hh>
#include <corps/mapfile.hh>
#include <corps/mapsetfile.hh>

#include "gui.hh"
#include "gui_about.hh"
#include "gui_busyreq.hh"
#include "gui_exception.hh"
#include "gui_mapwindow.hh"
#include "trashcan.hh"


extern GUI *gui;
extern Trashcan trash;



GUI::GUI(int &argc, char **&argv) throw() :
  Gtk_Main(&argc, &argv)
{
  pthread_mutex_init(&_lock, 0);
  pthread_mutex_init(&lock_lock, 0);

  gdk_imlib_init();
}


GUI::~GUI() throw()
{
  pthread_mutex_destroy(&lock_lock);
  pthread_mutex_destroy(&_lock);
}


void GUI::handle() throw()
{
  lock();

  connect_to_method(Gtk_Main::timeout(10000), this, &GUI::empty_trash);
  connect_to_method(Gtk_Main::timeout(50), this, &GUI::lock_queue);
  run();

  unlock();
}


void GUI::lock() throw()
{
  // if the GUI is already locked by us...
  pthread_mutex_lock(&lock_lock);
  if(lock_count > 0 && locker == pthread_self())
    {
      // increment lock count by one and return
      lock_count++;
      pthread_mutex_unlock(&lock_lock);
      return;
    }
  pthread_mutex_unlock(&lock_lock);

  // lock the GUI
  pthread_mutex_lock(&_lock);

  // set the lock count to one and tell that we are the locker
  pthread_mutex_lock(&lock_lock);
  lock_count = 1;
  locker = pthread_self();
  pthread_mutex_unlock(&lock_lock);
}


void GUI::unlock() throw()
{
  pthread_mutex_lock(&lock_lock);
  if(--lock_count == 0)
    pthread_mutex_unlock(&_lock);
  pthread_mutex_unlock(&lock_lock);
}


unsigned int GUI::freelock() throw()
{
  pthread_mutex_lock(&lock_lock);
  pthread_mutex_unlock(&_lock);
  unsigned int c = lock_count;
  lock_count = 0;
  pthread_mutex_unlock(&lock_lock);
  return c;
}


void GUI::relock(int c) throw()
{
  if(c == 0)
    return;
  pthread_mutex_lock(&_lock);
  pthread_mutex_lock(&lock_lock);
  lock_count = c;
  locker = pthread_self();
  pthread_mutex_unlock(&lock_lock);
}


void GUI::construct_map() throw()
{
  pthread_t thread;
  pthread_create(&thread, 0, &GUI::do_construct_map, 0);
  pthread_detach(thread);
}


void GUI::construct_map(const string &name) throw()
{
  string *n = new string(name);
  pthread_t thread;
  pthread_create(&thread, 0, &GUI::do_construct_map, n);
  pthread_detach(thread);
}


void *GUI::do_construct_map(string *n) throw()
{
  string name;
  if(n)
    {
      name.assign(*n);
      delete n;
    }

  gui->lock();
  GUI_BusyRequester *req =
    new GUI_BusyRequester(gettext("Please Wait..."), gettext("Please wait. Map is being loaded."));
  req->show();

  unsigned int c = gui->freelock();
  try
    {
      Map map;
      if(name.empty())
	{
	  MapSetFile msf;
	  msf.load_default();
	  map = Map(msf, 25, 25);
	}
      else
	map = MapFile(name);

      gui->relock(c);

      gui->lock();
      GUI_MapWindow *win = new GUI_MapWindow(map);
      win->show();
      gui->unlock();
    }
  catch(File_Exception e)
    {
      gui->relock(c);
      GUI::exception(e);
    }

  req->hide();
  delete req;
  gui->unlock();

  return 0; // dummy
}


void GUI::exception(const Exception &e) throw()
{
  gui->lock();
  GUI_Exception *ge = new GUI_Exception(e);
  ge->show();
  gui->unlock();
}


void GUI::about() throw()
{
  gui->lock();
  GUI_About *win = new GUI_About("MapTool ("PACKAGE") "VERSION,
				 gettext("CORPS map manipulator."));
  win->show();
  gui->unlock();
}


gint GUI::empty_trash() throw()
{
  trash.empty();

  return 1;
}


gint GUI::lock_queue() throw()
{
  unlock();

  struct timeval tv = { 0, 5 };
  select(0, 0, 0, 0, &tv);

  lock();

  return 1;
}
