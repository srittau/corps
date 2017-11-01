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

//FIXME: free images?

#include <i18n.hh>

#include <cstdlib>
#include <string>
#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <libintl.h>

#include <gdk_imlib.h>

#include <corps/exception.hh>
#include <corps/tools.hh>

#include "mapmodifier.hh"
#include "mapsetfile.hh"


#define MAX_SPECIALS 3
char *MapSetFile::special_names[] = { "Unknown", "Nothing", "Unseen" };


MapSetFile::MapSetFile() throw() :
  MapSet(),
  CORPS_XML(),

  pixmap_name(),
  modifier_name()
{
}


MapSetFile::MapSetFile(const string &fn) throw(File_Exception) :
  MapSet(),
  CORPS_XML(fn),

  pixmap_name(),
  modifier_name()
{
  load_internal(fn);
}


void MapSetFile::load(const string &fn) throw(File_Exception)
{
  CORPS_XML::load(fn);
  load_internal(fn);
}


void MapSetFile::load_named(const string &fn) throw(File_Exception)
{
  bool found = false;

  // try to load file by taking filename literally
  try
    {
      CORPS_XML::load(fn);
      found = true;
    }
  catch(File_Exception e)
    {
      if(static_cast<Exception>(e) != ENOENT)
	throw e;
    }

  // try to load load file by searching for filename in MapSet directory
  string new_fn(fn);
  if(!found)
    {
      try
	{
	  new_fn.insert(0, MAPSETDIR "/");
	  new_fn.append(".xml");
	  CORPS_XML::load(new_fn);
	}
      catch(File_Exception e)
	{
	  if(static_cast<Exception>(e) == ENOENT)
	    throw File_Exception(_("unknown map set"), fn);
	  else
	    throw e;
	}
    }

  load_internal(new_fn);
}


void MapSetFile::load_default() throw(File_Exception)
{
  load_named("generic");
}


void MapSetFile::load_internal(const string &filename) throw(File_Exception)
{
  try
    {
      try { find_element_path("MapSet"); }
      catch(CORPS_XML::Error e) { throw Exception(_("not a mapset file")); }
      try { find_element_path("MapSet/Meta"); }
      catch(CORPS_XML::Error e) { throw Exception(_("mapset corrupt: missing meta information")); }

      retrieve_name();
      retrieve_fieldsize();
      retrieve_pixmapfile();
      retrieve_fields();
      retrieve_modifierfile();
      retrieve_modifiers();
    }
  catch(Exception e)
    {
      throw File_Exception(e, filename);
    }

  // change to directory relative to this file
  string dirname(filename);
  char *olddir = 0;
  string::size_type pos = dirname.rfind('/');
  if(pos >= 0)
    {
      dirname.erase(pos);
      olddir = getcwd(0, 0);
      if(chdir(dirname.c_str()) != 0)
	throw File_Exception(errno, dirname);
    }

  // load pixmap and modifier files
  load_field_pixmap(pixmap_name);
  if(!modifier_name.empty())
    load_modifier_pixmap(modifier_name);

  // return to old directory
  if(!dirname.empty())
    {
      int r = chdir(olddir); 
      free(olddir);
      if(r != 0)
	throw File_Exception(errno, olddir);
    }
}


void MapSetFile::load_field_pixmap(const string &fn) throw(File_Exception)
{
  Gdk_Imlib::Image im(fn);
  if(!im.gdkobj())
    throw File_Exception(errno, fn);

  if(im.rgb_width() % width != 0 || im.rgb_height() % height != 0)
    throw File_Exception(_("image has wrong size"), fn);
  unsigned int images_per_line = im.rgb_width() / width;
  unsigned int lines = im.rgb_height() / height;
  if(images_per_line * lines < field_list.size())
    throw File_Exception(_("image has wrong size"), fn);

  unsigned int pos_in_line = 0;
  unsigned int line = 0;
  while(line * images_per_line + pos_in_line < field_list.size())
    {
      Gdk_Imlib::Image new_im;
      new_im.crop_and_clone(im,
			    pos_in_line * width,
			    line * height,
			    width,
			    height);
      field_list[line * images_per_line + pos_in_line].set_pixmap(new_im);

      if(++pos_in_line == images_per_line)
	{
	  pos_in_line = 0;
	  line++;
	}
    }
}


void MapSetFile::load_modifier_pixmap(const string &fn) throw(File_Exception)
{
  Gdk_Imlib::Image im(fn);
  if(!im.gdkobj())
    throw File_Exception(errno, fn);

  if(im.rgb_width() % width != 0 || im.rgb_height() % height != 0)
    throw File_Exception(_("image has wrong size"), fn);
  unsigned int images_per_line = im.rgb_width() / width;
  unsigned int lines = im.rgb_height() / height;
  if(images_per_line * lines < field_list.size())
    throw File_Exception(_("image has wrong size"), fn);

  unsigned int pos_in_line = 0;
  unsigned int line = 0;
  while(line * images_per_line + pos_in_line < modifier_list.size())
    {
      Gdk_Imlib::Image new_im;
      new_im.crop_and_clone(im,
			    pos_in_line * width,
			    line * height,
			    width,
			    height);
      modifier_list[line * images_per_line + pos_in_line].set_pixmap(new_im);

      if(++pos_in_line == images_per_line)
	{
	  pos_in_line = 0;
	  line++;
	}

    }
}


void MapSetFile::retrieve_name() throw(Exception)
{
  try
    {
      const CORPS_XML::Element e = find_element_path("MapSet/Meta/Name");
      name = e.get_content();
      if(name.empty())
	throw Exception(_("mapset corrupt: empty name"));
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("mapset corrupt: missing name"));
    }
}


void MapSetFile::retrieve_fieldsize() throw(Exception)
{
  CORPS_XML::Element e;

  try { e = find_element_path("MapSet/Images"); }
  catch(CORPS_XML::Error) { throw Exception(_("mapset corrupt: missing image information")); }

  try
    {
      CORPS_XML::Attribute a;
      char *endptr;
      a = e.find_attribute("width");
      width = strtoul(a.get_value().c_str(), &endptr, 10);
      if(*endptr)
        throw Exception(insert_text(_("mapset corrupt: invalid numeric argument: %s"), a.get_value()));
      a = e.find_attribute("height");
      height = strtoul(a.get_value().c_str(), &endptr, 10);
      if(*endptr)
        throw Exception(insert_text(_("mapset corrupt: invalid numeric argument: %s"), a.get_value()));
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("mapset corrupt: missing size information"));
    }
}


static char *special_ids[] = { "unknown", "nothing", "unseen" };
static char *special_names[] = { "Unknown", "Nothing", "Unseen" };
void MapSetFile::retrieve_pixmapfile() throw(Exception)
{
  try
    {
      const CORPS_XML::Element e = find_element_path("MapSet/Images/Pixmap");
      pixmap_name = e.find_attribute("uri").get_value();
      if(pixmap_name.empty())
        throw Exception(_("map corrupt: pixmap name empty"));

      // retrieve number of special fields
      CORPS_XML::Attribute a = e.find_attribute("specials");
      string specials = a.get_value();
      char *endptr;
      special_count = strtoul(a.get_value().c_str(), &endptr, 10);
      if(*endptr)
        throw Exception(insert_text(_("mapset corrupt: invalid numeric argument: %s"), a.get_value()));
      // sanity checks
      if(special_count < 3)
	throw Exception(_("mapset does not support FT_Unknown, FT_Nothing or FT_Unseen"));
      else if(special_count > MAX_SPECIALS)
	throw Exception(_("mapset has too many special fields"));

      // fill special names into field_list
      FieldType pos = 0;
      FieldType maxpos = special_count>3?3:special_count;
      while(pos < maxpos)
	{
	  Field nf(pos, special_ids[pos]);
	  nf.add_name("en", special_names[pos]);
	  //FIXME: add localized name
	  field_list.insert(field_list.end(), nf);
	  pos++;
	}
    }
  catch(CORPS_XML::Error e)
    {
      throw Exception(_("mapset corrupt: missing or wrong pixmap definition"));
    }
}


void MapSetFile::retrieve_fields() throw(Exception)
{
  try
    {
      FieldList::size_type first_field = field_list.size();

      CORPS_XML::Element e = find_element_path("MapSet/Images/Pixmap/IdList");
      ElementList children = e.get_children_type("Id");

      ElementList::size_type pos = 0;
      while(pos < children.size())
	{
	  try
	    {
	      string id = children[pos].find_attribute("id").get_value();
	      Field nf(FT_User + pos, id);
	      field_list.insert(field_list.end(), nf);
	    }
	  catch(CORPS_XML::Error e)
	    {
	      Exception(_("missing field id")).print_warning();
	    }
	  pos++;
	}

      // names
      e = find_element_path("MapSet/Images/Pixmap");
      children = e.get_children_type("FieldList");

      pos = 0;
      while(pos < children.size())
	{
	  string lang;
	  try { lang = e.find_attribute("xml:lang").get_value(); }
	  catch(...) {} // use default (empty string)
	  ElementList field_names = children[pos].get_children_type("FieldName");
	  ElementList::size_type pos2 = 0;
	  while(pos2 < field_names.size() && pos2 + first_field < field_list.size())
	    {
	      field_list[pos2 + first_field].add_name(lang, field_names[pos2].get_content());
	      pos2++;
	    }
	  pos++;
	}
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("mapset corrupt: missing or wrong pixmap definition"));
    }
}


//FIXME: handle multiple modifier files
void MapSetFile::retrieve_modifierfile() throw(Exception)
{
  try
    {
      const CORPS_XML::Element e = find_element_path("MapSet/Images/ModifierPixmap");
      modifier_name = e.find_attribute("uri").get_value();
      if(modifier_name.empty())
        throw Exception(_("map corrupt: modifier name empty"));
    }
  catch(CORPS_XML::Error e)
    {
      // CORPS_XML::NO_SUCH_ELEMENT isn't an error: in this case there aren't
      // any modifiers
      if(e != CORPS_XML::NO_SUCH_ELEMENT)
	throw Exception(_("mapset corrupt: wrong modifiers definition"));
    }
}


void MapSetFile::retrieve_modifiers() throw(Exception)
{
  try
    {
      CORPS_XML::Element e = find_element_path("MapSet/Images/ModifierPixmap/IdList");
      ElementList children = e.get_children_type("Id");

      ElementList::size_type pos = 0;
      while(pos < children.size())
	{
	  try
	    {
	      string id = children[pos].find_attribute("id").get_value();
	      Modifier s(pos, id);
	      modifier_list.insert(modifier_list.end(), s);
	    }
	  catch(CORPS_XML::Error e)
	    {
	      Exception(_("missing field id")).print_warning();
	    }
	  pos++;
	}

      // names
      e = find_element_path("MapSet/Images/ModifierPixmap");
      children = e.get_children_type("FieldList");

      pos = 0;
      while(pos < children.size())
	{
	  string lang;
	  try { lang = e.find_attribute("xml:lang").get_value(); }
	  catch(...) {} // use default (empty string)
	  ElementList modifier_names = children[pos].get_children_type("FieldName");
	  ElementList::size_type pos2 = 0;
	  while(pos2 < modifier_names.size() && pos2 < modifier_list.size())
	    {
	      modifier_list[pos2].add_name(lang, modifier_names[pos2].get_content());
	      pos2++;
	    }
	  pos++;
	}
    }
  catch(CORPS_XML::Error)
    {
      throw Exception(_("mapset corrupt: wrong modifiers definition"));
    }
}
