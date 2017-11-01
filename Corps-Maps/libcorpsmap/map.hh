#ifndef MAP_HH
#define MAP_HH

/*  Map class
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

#include <vector>

#include <gdk_imlib.h>
#include <gdk--/drawable.h>

#include "mapmodifier.hh"
#include "mapset.hh"

class Exception;


class Map {
public:
  typedef struct { unsigned long int width; unsigned long int height; } Size;
  class Field
  {
  public:
    Field() throw() : type(MapSet::FT_Unknown), modifiers() {}
    Field(MapSet::FieldType t) : type(t), modifiers() {}

    MapSet::FieldType get_type() const throw() { return type; }
    const ModifierList &get_modifiers() const throw() { return modifiers; }
    void add_modifier(const Modifier &m) throw();

  private:
    MapSet::FieldType type;
    ModifierList      modifiers;
  };
  typedef vector<Field> FieldList;

  Map() throw();
  // create an empty map with size
  Map(const MapSet &ms, int w, int h) throw();

  const string &get_name() const throw() { return name; }
  Size get_size() const throw() { Size s = {width, height}; return s; }
  unsigned long int get_width() const throw() { return width; }
  unsigned long int get_height() const throw() { return height; }
  const FieldList &get_fields() const throw() { return fields; }
  const MapSet &get_mapset() const throw() { return mapset; }

  void resize(Size s) throw();

  void construct_map(Gdk_Drawable &) const throw(Exception);

protected:
  string name;
  unsigned long int width;
  unsigned long int height;
  FieldList fields;
  MapSet mapset;
};

#endif // MAP_HH
