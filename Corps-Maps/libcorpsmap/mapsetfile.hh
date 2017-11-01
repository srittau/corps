#ifndef MAPSETFILE_HH
#define MAPSETFILE_HH

/*  MapSetFile class
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

#include <string>

#include <corps/exception.hh>
#include <corps/xml.hh>

#include "mapmodifier.hh"
#include "mapset.hh"


class MapSetFile : public MapSet, public CORPS_XML {
public:
  MapSetFile() throw();
  MapSetFile(const string &fn) throw(File_Exception);

  virtual void load(const string &fn) throw(File_Exception);
  void load_named(const string &fn) throw(File_Exception);
  void load_default() throw(File_Exception);

private:
  // do the actual loading
  void load_internal(const string &filename) throw(File_Exception);

  static char *special_names[];

  string pixmap_name;
  string modifier_name;

  void load_field_pixmap(const string &filename) throw(File_Exception);
  void load_modifier_pixmap(const string &filename) throw(File_Exception);

  void retrieve_name() throw(Exception);
  void retrieve_fieldsize() throw(Exception);
  void retrieve_pixmapfile() throw(Exception);
  void retrieve_fields() throw(Exception);
  void retrieve_modifierfile() throw(Exception);
  void retrieve_modifiers() throw(Exception);
};

#endif // MAPSETFILE_HH
