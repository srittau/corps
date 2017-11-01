/*  MapSet class
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
#include <cstring>
#include <cerrno>

#include <libintl.h>
#include <locale.h>

#include <corps/exception.hh>
#include <corps/tools.hh>

#include "mapset.hh"


template class MapSet::Piece<unsigned int>;


MapSet::MapSet() throw() :
  name(),
  width(0),
  height(0),
  field_list(),
  modifier_list(),
  special_count(0)
{
}


// fortunately we don't need to traverse through the list but can use
// random-access, since we store our fields in a continuous array
const MapSet::Field &MapSet::get_field(FieldType type) const throw()
{
  if(type >= 256)
    type += -256 + special_count;
  return field_list[type];
}


// fortunately we don't need to traverse through the list but can use
// random-access, since we store our fields in a continuous array
const MapSet::Modifier &MapSet::get_modifier(::Modifier::Type type) const throw()
{
  return modifier_list[type];
}


bool MapSet::is_valid_field(FieldType nr) const throw()
{
  FieldList::size_type pos = 0;
  while(pos < field_list.size())
    {
      if(field_list[pos].get_type() == nr)
	return true;
      pos++;
    }
  return false;
}


bool MapSet::is_valid_modifier(::Modifier::Type nr) const throw()
{
  ModifierList::size_type pos = 0;
  while(pos < modifier_list.size())
    {
      if(modifier_list[pos].get_type() == nr)
	return true;
      pos++;
    }
  return false;
}


MapSet::FieldType MapSet::resolve_field_name(const string &n) const throw(Exception)
{
  char *endptr;
  MapSet::FieldType f = strtol(n.c_str(), &endptr, 10);
  if(endptr[0])
    {
      // name is a string: search string in list
      FieldList::size_type pos = 0;
      while(pos < field_list.size())
	{
	  if(!(strcasecmp(field_list[pos].get_id().c_str(), n.c_str())))
	    return field_list[pos].get_type();
	  pos++;
	}
      // not found: throw exception
      string s(_("unknown map set field definition: \"%s\""));
      throw Exception(insert_text(s, n));
    }

  // name is a numeric literal: search in list of existing fields
  if(!is_valid_field(f))
    {
      string s(_("invalid map set field definition: \"%s\""));
      throw Exception(insert_text(s, n));
    }

  return f;
}


MapSet::ModifierType MapSet::resolve_modifier_name(const string &n) const throw(Exception)
{
  char *endptr;
  ModifierType m = strtol(n.c_str(), &endptr, 10);
  if(endptr[0])
    {
      // name is a string: search string in list
      ModifierList::size_type pos = 0;
      while(pos < modifier_list.size())
	{
	  if(!(strcasecmp(modifier_list[pos].get_id().c_str(), n.c_str())))
	    return modifier_list[pos].get_type();
	  pos++;
	}
      // not found: throw exception
      string s(_("unknown map set modifier definition: \"%s\""));
      throw Exception(insert_text(s, n));
    }

  // name is a numeric literal: search in list of existing fields
  if(!is_valid_modifier(m))
    {
      string s(_("invalid map set modifier definition: \"%s\""));
      throw Exception(insert_text(s, n));
    }

  return m;
}

/*************************************************************************/

template <class T>
string MapSet::Piece<T>::get_name() const throw()
{
  char *e;
  e = getenv("LANGUAGE");
  if(!e)
    e = getenv("LC_ALL");
  if(!e)
    e = getenv("LANG");
  if(!e)
    e = "";

  return get_name(e);
}


// FIXME: smarter algorithm that recognizes things like de_DE
template <class T>
string MapSet::Piece<T>::get_name(const string &lang) const throw()
{
  vector<i18n_name>::size_type pos;

  pos = 0;
  while(pos < names.size())
    {
      if(names[pos].lang == lang)
	return names[pos].name;
      pos++;
    }

  // lang not found, use default name
  pos = 0;
  while(pos < names.size())
    {
      if(names[pos].lang.empty())
	return names[pos].name;
      pos++;
    }

  // default not found, use first entry
  if(names.size() > 0)
    return names[0].name;

  // no names were defined, fall back to id
  return id;
}


template <class T>
void MapSet::Piece<T>::add_name(const string &lang, const string &name) throw()
{
  struct i18n_name i = { lang, name };
  names.insert(names.end(), i);
}
