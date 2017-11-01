/*  The Maniax - an adventure for CORPS
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

#include <config.h>

#include <cstdlib>

#include <libintl.h>

#include <omniORB2/CORBA.h>

#include <corps/corbaexception.hh>
#include <corps/exception.hh>
#include <corps/gamelist-wrapper.hh>
#include <corps/orb.hh>

#include "arghandler.hh"
#include "game.hh"


extern CORPS_ORB *orb;

GameList_Wrapper gamelist;


// announce game to server or print out id
void announce_game(const string &id, Game_Impl &o) throw(CorbaException)
{
  if(id.empty())
    cout << orb->object_to_string(&o) << endl;
  else
    {
      CORBA::Object_var ptr = orb->string_to_object(id);
      RolePlaying::GameList_var gl_server_o =
	RolePlaying::GameList::_narrow(ptr);
      if(CORBA::is_nil(gl_server_o))
	throw Exception("specified object reference is not a game list");
      gamelist = GameList_Wrapper(gl_server_o);
      gamelist._register(&o);
    }
}


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

      /* CORBA initialization */
      CORPS_ORB orb_ref(argc, argv);
      orb = &orb_ref;

      ArgHandler args(argc, argv);

      Game *game = new Game;
      game->_obj_is_ready(orb_ref.getBOA());

      announce_game(args.get_register_with(), *game);
      orb_ref.run();
      gamelist.unregister();

      game->_dispose();

    }
  catch(CorbaException e)
    {
      e.print();
      exit(1);
    }
  catch(Exception e)
    {
      e.print();
      exit(1);
    }

  exit(0);
}
