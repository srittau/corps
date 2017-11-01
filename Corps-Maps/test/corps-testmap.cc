/*  Test suite for CORPS maps
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

#include <iostream>

#include <gdk_imlib.h>

#include <corps/exception.hh>

#include "mapfile.hh"


int main(int argc, char *argv[])
{
  gdk_init(&argc, &argv);
  gdk_imlib_init();

  if(argc < 2)
    {
      cerr << "Please supply at least one map file at the command line\n";
      return 1;
    }

  for(int x = 1; x < argc; x++)
    {
      try
	{
	  cout << "*** trying to load " << argv[x] << endl;
	  MapFile mf(argv[x]);
	  cout << "*** " << argv[x] << " successfully loaded\n";
	}
      catch(File_Exception e)
	{
	  e.print();
	  cout << "*** failed loading " << argv[x] << endl;
	}
    }

  return 0;
}
