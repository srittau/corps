/*  Startup of GCorps
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

#include <cstdlib>
#include <time.h>
#include <libintl.h>

#include <corps/exception.hh>
#include <corps/orb.hh>

#include "arghandler.hh"
#include "client.hh"
#include "gui.hh"
#include "trashcan.hh"


Trashcan trash;
GUI *gui = 0;
extern CORPS_ORB *orb;


int main(int argc, char *argv[]) throw()
{
  int result = 0;

  /* set up random number generator */
  srandom(static_cast<long int>(time(0))); // FIXME: better random value

  /* set up i18n */
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);

  try
    {
      CORPS_ORB orb_ref(argc, argv);
      orb = &orb_ref;
      orb_ref.ready();

      GUI gui_ref(argc, argv);
      gui = &gui_ref;

      ArgHandler(argc, argv);
      new Client;

      gui_ref.handle();

    }
  catch(Exception e)
    {
      e.print();
      result = 1;
    }

  Client::delete_all();

  return result;
}
