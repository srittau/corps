#ifndef MAPFILE_HH
#define MAPFILE_HH

/*  MapFile class
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

#include <corps/xml.hh>

#include "map.hh"


class File_Exception;
class Exception;


class MapFile : public Map, public CORPS_XML {
public:
  MapFile() throw();
  MapFile(const string &filename) throw(File_Exception);

private:
  void retrieve_name() throw(Exception);
  void retrieve_size() throw(Exception);
  void retrieve_mapset() throw(Exception);
  void retrieve_fields() throw(Exception);

  Field element_to_field(const CORPS_XML::Element e) const throw();
  Modifier element_to_modifier(const CORPS_XML::Element e) const throw(Exception);
};

#endif // MAPFILE_HH
