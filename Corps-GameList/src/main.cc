/*  GameList server for CORPS
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

#include <signal.h>
#include <libintl.h>

#include <corps/exception.hh>
#include <corps/orb.hh>

#include "arghandler.hh"
#include "gamelist.hh"


extern CORPS_ORB *orb;
_GameList *gl = 0;



void dump_database(int)
{
  gl->dump_to_screen();
}


int main(int argc, char *argv[])
{
  /* Set up i18n. */
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);

  try
    {
      CORPS_ORB orb_ref(argc, argv);
      orb = &orb_ref;
      ArgHandler(argc, argv);

      gl = new _GameList;
      gl->_obj_is_ready(orb_ref.getBOA());

      cout << orb_ref.object_to_string(gl) << endl;

      // dump database to screen, if we receive SIGUSR1
      signal(SIGHUP, &dump_database);

      orb_ref.run();
    }
  catch(Exception &e)
    {
      e.print();
      delete &e;
      exit(1);
    }

  return 0;
}
