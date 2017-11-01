/*  Argument handler
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

#include <iostream>
#include <getopt.h>
#include <libintl.h>

#include <corps/exception.hh>
#include <corps/tools.hh>

#include "arghandler.hh"


struct option ArgHandler::ArgArray[] = {
    { "version",            no_argument,       0, 'v' },
    { "help",               no_argument,       0, 'h' },
    { "register-with",      required_argument, 0, 'r' },
    { "name",               required_argument, 0, 'n' },
    { "description",        required_argument, 0, 'd' },
    { "system-name",        required_argument, 0, 'N' },
    { "system-description", required_argument, 0, 'D' },
    { "language",           required_argument, 0, 'l' },
    { 0, 0, 0, 0 }
};
const char ArgHandler::OptString[] = "vhr:n:d:N:D:l:";


ArgHandler::ArgHandler(int argc, char *argv[]) throw() :
  gamelist_server(),
  game_name("Generic"),
  game_description("A generic game"),
  system_name("Generic"),
  system_description("A generic text-only system engine. The game is "
		     "completely controlled by the game-master. No "
		     "system-specific hooks are implemented."),
  language()
{
  int c;
  int index = 0;

  while((c = getopt_long(argc, argv, OptString, ArgArray, &index)) != -1)
    {
      switch(c)
	{
	case 'h':
	  cout << insert_text(gettext("Usage: %s [OPTIONS]"), argv[0]) << endl << endl
	       << gettext("Option summary:\n\n"
			  " -h --help          - print this text and exit\n"
			  " -v --version       - print version information and exit\n"
			  " -r --register-with - specify meta-server to register with\n"
			  " -n --name          - name of game to play\n"
			  " -d --description   - description of game to play\n"
			  " -N --system-name   - name of system to use\n"
			  " -D --system-description - description of system to use\n"
			  " -l --language      - language to use for messages transmitted to clients\n"
			  "\nReport bugs to srittau@jroger.in-berlin.de\n");
	  exit(0);
	case 'v':
	  cout << "TextServer ("PACKAGE") "VERSION"\n"
	    "Copyright (C) 1998-99 Sebastian Rittau\n";
	  exit(0);
	case 'r':
	  if(!gamelist_server.empty())
	    {
	      Exception(gettext("unique option specified twice")).print();
	      exit(1);
	    }
	  gamelist_server.assign(optarg);
	  break;
	case 'n':	  
	  game_name.assign(optarg);
	  break;
	case 'd':
	  game_description.assign(optarg);
	  break;
	case 'N':
	  system_name.assign(optarg);
	  break;
	case 'D':
	  system_description.assign(optarg);
	  break;
	case 'l':
	  language.assign(optarg);
	  break;
	case '?':
	  exit(1);
	}
    }

  if(argc != optind)
    {
      Exception(gettext("invalid number of arguments")).print();
      exit(1);
    }
}
