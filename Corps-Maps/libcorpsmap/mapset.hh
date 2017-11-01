#ifndef MAPSET_HH
#define MAPSET_HH

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

#include <string>
#include <vector>

#include <gdk--/extra/imlib.h>

#include "mapmodifier.hh"

class Exception;


class MapSet {
public:
  template <class T>
  class Piece {
  public:
    Piece() throw() : type(0), id(), names(), pixmap() {}
    Piece(T t, const string &i) throw() : type(t), id(i), names(), pixmap() {}

    T get_type() const throw() { return type; }
    string get_id() const throw() { return id; }
    string get_name() const throw();
    string get_name(const string &lang) const throw();
    const Gdk_Imlib::Image &get_pixmap() const throw() { return pixmap; }

    void add_name(const string &lang, const string &name) throw();
    void set_pixmap(const Gdk_Imlib::Image &p) throw() { pixmap = p; }

  private:
    struct i18n_name { string lang; string name; };

    T                 type;
    string            id;
    vector<i18n_name> names;
    Gdk_Imlib::Image  pixmap;
  };

  typedef unsigned int FieldType;
  typedef Piece<FieldType> Field;
  typedef vector<Field> FieldList;
  typedef ::Modifier::Type ModifierType;
  typedef Piece<ModifierType> Modifier;
  typedef vector<Modifier> ModifierList;

  // see roleplaying.idl and <corps/roleplaying.h>
  static const unsigned int FT_Unknown = 0;
  static const unsigned int FT_Nothing = 1;
  static const unsigned int FT_Unseen  = 2;
  static const unsigned int FT_User    = 256;

  MapSet() throw();

  const string &get_name() const throw() { return name; }
  unsigned int get_width() const throw() { return width; }
  unsigned int get_height() const throw() { return height; }
  const Field &get_field(FieldType type) const throw();
  const FieldList &get_field_list() const throw() { return field_list; }
  const Modifier &get_modifier(ModifierType type) const throw();
  const ModifierList &get_modifier_list() const throw() { return modifier_list; }

  bool is_valid_field(FieldType nr) const throw();
  bool is_valid_modifier(ModifierType nr) const throw();
  // the next two function throw an exception if N can't be resolved
  FieldType resolve_field_name(const string &n) const throw(Exception);
  ModifierType resolve_modifier_name(const string &n) const throw(Exception);

protected:
  string name;
  unsigned int width;
  unsigned int height;
  FieldList field_list;
  FieldType special_count;
  ModifierList modifier_list;
};

#endif // MAPSET_HH
