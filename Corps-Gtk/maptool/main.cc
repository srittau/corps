/*  MapGenerator for corps-gtk
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

#include <libintl.h>

#include <corps/file_exception.hh>
#include <corps/mapfile.hh>
#include <corps/mapsetfile.hh>

#include "arghandler.hh"
#include "gui.hh"
#include "trashcan.hh"


GUI *gui = 0;
Trashcan trash;



void load_maps(const ArgHandler::ArgList &maps) throw(File_Exception, Exception)
{
  //FIXME: if building of all maps fails, exit program
  if(maps.empty())
    gui->construct_map();
  else
    {
      ArgHandler::ArgList::size_type n;
      for(n = 0; n < maps.size(); n++)
	gui->construct_map(maps[n]);
    }
}


int main(int argc, char **argv) throw()
{
  // set up i18n
  setlocale(LC_ALL, "");
  textdomain(PACKAGE);

  GUI gui_ref(argc, argv);
  gui = &gui_ref;

  try
    {
      ArgHandler args(argc, argv);

      load_maps(args.get_extra_args());

      gui_ref.handle();
    }

  catch(File_Exception e)
    {
      e.print();
      exit(1);
    }
  catch(Exception e)
    {
      e.print();
      exit(1);
    }

  return 0;
}
