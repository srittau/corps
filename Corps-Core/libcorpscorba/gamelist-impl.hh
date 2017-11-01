#ifndef GAMELIST_IMPL_HH
#define GAMELIST_IMPL_HH

/*  RolePlaying::GameList implementation
    Copyright (C) 1998-99 Sebastian Rittau

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

#include "game-wrapper.hh"
#include "roleplaying.hh"


class Exception;


class GameList_Impl : public RolePlaying::_sk_GameList
{
public:
  GameList_Impl() throw();
  virtual ~GameList_Impl() throw();

protected:
  virtual ::GameList get_list() throw(CorbaException) = 0;
  virtual string _register(Game_Wrapper g) throw(CorbaException) = 0;
  virtual void _unregister(const string &id) throw(CorbaException) = 0;

private:
  virtual GList *list() throw(CORBA::Exception);
  virtual char *_cxx_register(RolePlaying::Game_ptr g) throw(CORBA::Exception);
  virtual void unregister(const char *id) throw(CORBA::Exception);
};

#endif // GAMELIST_IMPL_HH
