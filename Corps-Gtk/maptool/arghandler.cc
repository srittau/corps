/*  Argument handling class
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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <libintl.h>

#include <corps/exception.hh>

#include "arghandler.hh"



struct option ArgHandler::arguments[] =
{
  {"version", no_argument, 0, 'v'},
  {"help", no_argument, 0, 'h'},
  {0, 0, 0, 0}
};


ArgHandler::ArgHandler(int argc, char *argv[]) throw(Exception)
{
  int c, index = 0;

  while((c = getopt_long(argc, argv, "hv", arguments, &index)) > -1)
    {
      switch(c)
	{
	case 'h':
	  printf(gettext("Usage: %s [MAPS...]\n\n"
			 "Report bugs to <srittau@jroger.in-berlin.de>\n"),
		 argv[0]);
	  exit(EXIT_SUCCESS);
	case 'v':
	  printf("MapTool (" PACKAGE ") " VERSION "\n"
		 "Copyright (C) 1998-99 Sebastian Rittau.\n");
	  exit(EXIT_SUCCESS);
	default:
	  exit(EXIT_FAILURE);
	}
    }

  while(optind < argc)
    {
      extra_args.insert(extra_args.end(), string(argv[optind]));
      optind++;
    }
}
