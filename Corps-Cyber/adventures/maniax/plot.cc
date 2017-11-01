/*  Plot for CORPS adventure "The Maniax"
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

#include <pthread.h>

#include "plot.hh"


void Plot::start() throw()
{
  pthread_t thread;
  pthread_create(&thread, 0, &try_plot_handler, this);
  pthread_detach(thread);
}


void Plot::plot_handler() throw()
{
  //FIXME
}

void *Plot::try_plot_handler(void *o) throw()
{
  static_cast<Plot *>(o)->plot_handler();
  return 0;
}
