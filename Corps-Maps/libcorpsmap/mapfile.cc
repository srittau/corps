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

#include <i18n.hh>

#include <cstdlib>
#include <string>

#include <libintl.h>

#include <corps/exception.hh>
#include <corps/tools.hh>

#include "mapfile.hh"
#include "mapsetfile.hh"


MapFile::MapFile() throw() :
  Map(),
  CORPS_XML()
{
}


MapFile::MapFile(const string &filename) throw(File_Exception) :
  Map(),
  CORPS_XML(filename)
{
  try
    {
      retrieve_name();
      retrieve_size();
      retrieve_mapset();
      retrieve_fields();
    }
  catch(Exception e)
    {
      throw File_Exception(e, filename);
    }
}


void MapFile::retrieve_name() throw(Exception)
{
  try
    {
      CORPS_XML::Element e = find_element_path("Map/Meta/Name");
      name = e.get_content();
      if(name.empty())
	throw Exception(_("map corrupt: empty name"));
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("map corrupt: missing name"));
    }
}


void MapFile::retrieve_size() throw(Exception)
{
  try
    {
      const CORPS_XML::Element e = find_element_path("Map/Meta/Size");
      CORPS_XML::Attribute a;
      char *endptr;
      a = e.find_attribute("width");
      width = strtoul(a.get_value().c_str(), &endptr, 10);
      if(*endptr)
	throw Exception(insert_text(_("map corrupt: invalid numeric argument: %s"), a.get_value()));
      a = e.find_attribute("height");
      height = strtoul(a.get_value().c_str(), &endptr, 10);
      if(*endptr)
	throw Exception(insert_text(_("map corrupt: invalid numeric argument: %s"), a.get_value()));
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("map corrupt: missing size information"));
    }
}


void MapFile::retrieve_mapset() throw(Exception)
{
  string mapset_name("generic");

  try
    {
      const CORPS_XML::Element e = find_element_path("Map/Meta/MapSet");
      mapset_name = e.find_attribute("name").get_value();
      if(mapset_name.empty())
	throw Exception(_("map corrupt: pixmap name empty"));
    }
  catch(CORPS_XML::Error e)
    {
      if(e == CORPS_XML::NO_SUCH_ATTRIBUTE)
	throw Exception(_("map corrupt: pixmap name missing"));
    }

  try
    {
      MapSetFile msf;
      msf.load_named(mapset_name);
      mapset = msf;
    }
  catch(File_Exception e)
    {
      throw Exception(e.get_error_string());
    }
}


void MapFile::retrieve_fields() throw(Exception)
{
  try
    {
      const CORPS_XML::Element e = find_element_path("Map/FieldList");
      const CORPS_XML::ElementList fs = e.get_children_type("Field");

      if(fs.size() != width * height)
	throw Exception(_("map corrupt: list of fields doesn't match map size"));

      unsigned int pos = 0;
      while(pos < fs.size())
	{
	  fields.insert(fields.end(), element_to_field(fs[pos]));
	  pos++;
	}
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("map corrupt: list of fields missing"));
    }
}


MapFile::Field MapFile::element_to_field(const CORPS_XML::Element e) const throw()
{
  Field f;

  // get type of field
  try
    {
      // get "type" attribute from element
      CORPS_XML::Attribute a;
      try { a = e.find_attribute("type"); }
      catch(CORPS_XML::Error) { throw Exception(_("map corrupt: field has no type")); }
      // get type value from mapset
      f = Field(mapset.resolve_field_name(a.get_value()));
    }
  // if an error occurs, f will be of type FT_Unknown
  catch(Exception e) { e.print_warning(); }

  // get modifiers (if any)
  ElementList children = e.get_children_type("Modifier");
  unsigned int pos = 0;
  while(pos < children.size())
    {
      try { f.add_modifier(element_to_modifier(children[pos])); }
      catch(Exception e) { e.print_warning(); }
      pos++;
    }

  return f;
}


Modifier MapFile::element_to_modifier(const CORPS_XML::Element e) const throw(Exception)
{
  Modifier::Type type;

  // get "type" attribute from element
  CORPS_XML::Attribute a;
  try { a = e.find_attribute("type"); }
  catch(...) { throw Exception(_("map corrupt: modifier has no type")); }

  // get type value from mapset
  type = mapset.resolve_modifier_name(a.get_value());

  // get depth of modifier
  Modifier::Depth depth = 0;
  try
    {
      a = e.find_attribute("depth");
      char *endptr;
      depth = static_cast<Modifier::Depth>(strtoul(a.get_value().c_str(),
						   &endptr,
						   10));
      if(*endptr)
	{
	  // print warning and use default (0)
	  Exception e(insert_text(_("map corrupt: invalid numeric argument: %s"),
				  a.get_value()));
	  e.print_warning();
	  depth = 0;
	}
      else if(depth < -9999 || depth > 9999)
	{
	  // print warning and use default (0)
	  Exception e(insert_text(_("map corrupt: depth out of range: %s"),
				  a.get_value()));
	  e.print_warning();
	  depth = 0;
	}
    }
  catch(...) {} // use default (0)

  return Modifier(type, depth);
}
