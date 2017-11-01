#ifndef CLIENTMAP_IMPL_HH
#define CLIENTMAP_IMPL_HH

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

class Client_GUI;
class Exception;


class ClientMap_Impl : public virtual RolePlaying::_sk_MIMEHandlerMap
{
public:
  ClientMap_Impl(Client_GUI &g) throw();
  virtual ~ClientMap_Impl() throw() {}

  // RolePlaying::MIMEHandlerBase
  virtual char *Type() throw(CORBA::NO_MEMORY);

  // RolePlaying::MIMEHandlerMap
  virtual void newMap(const RolePlaying::Map::Position &size, const RolePlaying::Map::PackedFields &f, const char *ms) throw();
  virtual void modifyFields(const RolePlaying::Map::Fields &f, const char *ms) throw();
  virtual void moveMap(const RolePlaying::Map::Position &lefttop, const RolePlaying::Map::Position &rightbottom) throw();

private:
  Client_GUI &gui;
};

#endif // CLIENTMAP_IMPL_HH
