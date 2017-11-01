/*  ArgHandler object for GameList server
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

#include "arghandler.hh"


struct option ArgHandler::ArgArray[] = {
    { "version", no_argument,       0, 'v' },
    { "help",    no_argument,       0, 'h' },
    { 0, 0, 0, 0 }
};
#define OPT_STRING "hv"


ArgHandler::ArgHandler(int argc, char **argv) throw(Exception &)
{
  int c;
  int index = 0;

  while((c = getopt_long(argc, argv, OPT_STRING, ArgArray, &index)) != -1)
    {
      switch(c)
	{
	case 'h':
	  cout << gettext("Option summary:\n\n"
			  " -h --help          - print this text and exit\n"
			  " -v --version       - print version information and exit\n"
			  "\nReport bugs to srittau@jroger.in-berlin.de\n");
	  exit(0);
	case 'v':
	  cout << "GameList-Server ("PACKAGE") 0.0.0\n"
	    "Copyright (C) 1998 Sebastian Rittau\n";
	  exit(0);
	case '?':
	  exit(1);
        }
    }

  if(optind != argc)
    {
      Exception(gettext("invalid number of arguments")).print();
      exit(1);
    }
}
