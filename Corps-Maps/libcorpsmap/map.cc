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

#include <i18n.hh>

#include <cerrno>

#include <libintl.h>

#include <gdk_imlib.h>
#include <gdk--/drawable.h>

#include <corps/exception.hh>

#include "map.hh"
#include "mapset.hh"


#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif // MAX

#ifndef MIN
#define MIN(x,y) ((x)>(y)?(y):(x))
#endif //MIN


Map::Map() throw() :
  name(),
  width(0),
  height(0),
  fields(),
  mapset()
{
}


Map::Map(const MapSet &ms, int w, int h) throw() :
  name(),
  width(w),
  height(h),
  fields(),
  mapset(ms)
{
  for(int x = 0; x < w; x++)
    {
      for(int y = 0; y < h; y++)
	fields.insert(fields.end(), Field(MapSet::FT_Unknown));
    }
}


void Map::resize(Size s) throw()
{
  FieldList::iterator i = fields.begin();

  unsigned long int new_height = MAX(height, s.height);

  // add/remove lines
  if(height > s.height)
    {
      for(unsigned long int a = 0; a < width * (height - s.height); a++)
	fields.erase(fields.end());
    }
  else if(height < s.height)
    {
      for(unsigned long int a = 0; a < width * (s.height - height); a++)
	fields.insert(fields.end(), Field(MapSet::FT_Unknown));
    }
  height = s.height;

  // add/remove fields at the end of row
  if(width != s.width)
    {
      unsigned long int y = 0;
      while(y < height)
	{
	  i = &i[MIN(width,s.width)];
	  if(width > s.width)
	    for(unsigned long int x = 0; x < (width - s.width); x++)
	      fields.erase(i);
	  else // width < s.width
	    for(unsigned long int x = 0; x < (s.width - width); x++)
	      {
		i = fields.insert(i, Field(MapSet::FT_Unknown));
		i++;
	      }
	  y++;
	}
    }
  width = s.width;
}


void Map::construct_map(Gdk_Drawable &win) const throw(Exception)
{
  if(!width || !height)
    throw Exception(Exception::INTERNAL_ERROR);

  for(MapSet::FieldType y = 0; y < height; y++)
    {

      for(MapSet::FieldType x = 0; x < width; x++)
	{
	  Gdk_Imlib::Image new_im;
	  const Field &field = fields[y * width + x];

	  new_im = mapset.get_field(field.get_type()).get_pixmap();
	  new_im.paste(win,
		       x * mapset.get_width(),
		       y * mapset.get_height(),
		       mapset.get_width(),
		       mapset.get_height());

	  // modifiers
	  MapSet::ModifierList::size_type mod_num = 0;
	  const ModifierList modifiers = field.get_modifiers();
	  while(mod_num < modifiers.size())
	    {
	      new_im =
		mapset.get_modifier(modifiers[mod_num].get_type()).get_pixmap();
	      new_im.paste(win,
			   x * mapset.get_width(),
			   y * mapset.get_height(),
			   mapset.get_width(),
			   mapset.get_height());
	      mod_num++;
	    }
	}
    }
}

/***************************************************************************/

void Map::Field::add_modifier(const Modifier &m) throw()
{
  ModifierList::size_type pos = 0;
  while(pos < modifiers.size())
    {
      if(m.get_depth() > modifiers[pos].get_depth())
	{
	  modifiers.insert(&modifiers[pos], m);
	  return;
	}
      pos++;
    }
  modifiers.insert(modifiers.end(), m);
}
