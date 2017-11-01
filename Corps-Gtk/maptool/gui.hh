#ifndef GUI_HH
#define GUI_HH

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

#include <pthread.h>

#include <gtk--/main.h>


class Exception;
class Map;


class GUI : public Gtk_Main
{
public:
  GUI(int &argc, char **&argv) throw();
  virtual ~GUI() throw();

  void handle() throw();

  void lock() throw();
  void unlock() throw();
  unsigned int freelock() throw();
  void relock(int c) throw();

  static void construct_map() throw();
  static void construct_map(const string &name) throw();
  static void exception(const Exception &e) throw();
  static void about() throw();

private:
  // NAME may be 0, its ownership changes to this function
  static void *do_construct_map(string *name) throw();

  pthread_mutex_t _lock;
  pthread_mutex_t lock_lock;
  pthread_t locker;
  unsigned int lock_count;

  gint empty_trash() throw();
  gint lock_queue() throw();
};

#endif /* GUI_HH */
