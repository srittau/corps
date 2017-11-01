/*  Simple text-only server for corps-servers
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

#include <time.h>
#include <libintl.h>

#include <corps/exception.hh>
#include <corps/gamelist-wrapper.hh>
#include <corps/orb.hh>

#include "arghandler.hh"
#include "game.hh"


ArgHandler *args = 0;
extern CORPS_ORB *orb;


int main(int argc, char *argv[])
{
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

      // argument handling
      ArgHandler args_ref(argc, argv);
      args = &args_ref;

      Game *game = new Game;
      game->_obj_is_ready(orb_ref.getBOA());

      try {

	const string &gl_server = args_ref.getGLServer();
	if(gl_server.empty())
	  {
	    // print out game object id
	    cout << orb_ref.object_to_string(game) << endl;
	    // main loop
	    orb_ref.run();
	  }
	else
	  {
	    // announce game to game list server
	    CORBA::Object_var o = orb_ref.string_to_object(gl_server);
	    RolePlaying::GameList *glso = RolePlaying::GameList::_narrow(o);
	    GameList_Wrapper gl_server_o(glso);
	    gl_server_o._register(game);
	    // main loop
	    orb_ref.run();
	    // unregister game from game list server
	    try { gl_server_o.unregister(); } catch(...) {}
	  }

	game->_dispose();
      } catch(...) { game->_dispose(); throw; }

    }
  catch(Exception &e)
    {
      e.print();
      delete &e;
      exit(1);
    }

  exit(0);
}
