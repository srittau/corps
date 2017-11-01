/*  A simple text-only CORPS client
    Copyright (C) 1999-2000 Sebastian Rittau

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

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <pthread.h>
#include <libintl.h>

#include <corps/corbaexception.hh>
#include <corps/game-wrapper.hh>
#include <corps/orb.hh>

#include "arghandler.hh"
#include "client.hh"
#include "gamelist.hh"


extern CORPS_ORB *orb;


pthread_mutex_t stdin_lock;


#define BUFFER_SIZE 1024
int main_loop(Game_Wrapper &game) throw()
{
  for(;;)
    {
      char buffer[BUFFER_SIZE];
      //FIXME: stdin lock
      //FIXME      sleep(100); //FIXME
      cout << "hmm...\n"; //FIXME
      cout.flush();
      cin.getline(buffer, BUFFER_SIZE, '\n');
      cout << "blubb: " << buffer << endl; //FIXME
      //FIXME      game.print(buffer);
      sleep(1); //FIXME
    }
}


#include <cstdio> //FIXME
int main(int argc, char *argv[])
{
  int ret = 0;

  // set up i18n
  setlocale(LC_ALL, "");
  textdomain(PACKAGE);

  try
    {

      CORPS_ORB orb_ref(argc, argv);
      orb = &orb_ref;

      ArgHandler args(argc, argv);

      // get the game object
      Game_Wrapper game;

      // if not a game, but a gamelist was specified...
      if(args.get_game().empty())
	{
	  // ... get game from gamelist ...
	  GameList_Handler list(args.get_list());
	  game = list.get_game();
	}
      else
	{
	  // ... otherwise get game from string supplied as argument
	  printf("10\n"); //FIXME
	  CORBA::Object_var o;
	  printf("11\n"); //FIXME
	  o = orb_ref.string_to_object(args.get_game());
	  printf("12\n"); //FIXME
	  RolePlaying::Game_var game_o = RolePlaying::Game::_narrow(o);
	  printf("13\n"); //FIXME
	  if(CORBA::is_nil(game_o))
	    throw Exception(gettext("specified object reference is not a game"));
	  printf("14\n"); //FIXME
	  game = game_o;
	  printf("15\n"); //FIXME
	}

      printf("0\n"); //FIXME
      // now set up client and join game
      Client *cl = new Client;
      cl->_obj_is_ready(orb_ref.getBOA());
      try
	{
	  game.join(cl);
	  cout << gettext("***Connected***") << endl;
	}
      catch(Exception e)
	{
	  cl->_dispose();
	  throw e;
	}

      // enter main loop
      printf("1\n"); //FIXME
      orb_ref.ready();
      printf("2\n"); //FIXME
      ret = main_loop(game);
      printf("3\n"); //FIXME

      // free client
      cl->_dispose();

    }
  catch(Exception e)
    {
      e.print();
      ret = 1;
    }

  return ret;
}
