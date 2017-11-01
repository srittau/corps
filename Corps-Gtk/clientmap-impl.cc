/*  x-rpg/map MIME Type implementation
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

#include <corps/roleplaying.hh>

#include "clientmap-impl.hh"

class Client_GUI;


ClientMap_Impl::ClientMap_Impl(Client_GUI &g) throw() :
  _sk_MIMEHandlerMap(),

  gui(g)
{
}


RolePlaying::MIMEType ClientMap_Impl::Type() throw(CORBA::NO_MEMORY)
{
  char *ret = CORBA::string_dup("x-rpg/map");
  if(!ret)
    throw CORBA::NO_MEMORY();
  return ret;
}


void ClientMap_Impl::newMap(const RolePlaying::Map::Position &size,
			    const RolePlaying::Map::PackedFields &f,
			    const char *ms) throw()
{
  //FIXME
}


void ClientMap_Impl::modifyFields(const RolePlaying::Map::Fields &f,
				  const char *ms) throw()
{
  //FIXME
}


void ClientMap_Impl::moveMap(const RolePlaying::Map::Position &lefttop,
			     const RolePlaying::Map::Position &rightbottom)
  throw()
{
  //FIXME
}
