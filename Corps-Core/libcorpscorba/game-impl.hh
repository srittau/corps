#ifndef GAME_IMPL_HH
#define GAME_IMPL_HH

/*  RolePlaying::Game implementation
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

#include "roleplaying.hh"


class Client_Wrapper;
class CorbaException;


class Game_Impl : public RolePlaying::_sk_Game
{
public:
  Game_Impl(const RolePlaying::System_var &sys) throw();
  virtual ~Game_Impl() throw() {}

protected:
  virtual string get_name() throw(CorbaException)
    { return _name; }
  virtual string get_description() throw(CorbaException)
    { return _description; }
  virtual RolePlaying::System_var get_system_o() throw(CorbaException)
    { return _system; }
  virtual unsigned int get_type() throw(CorbaException)
    { return game_type; }
  virtual string _join(Client_Wrapper wrapper) throw(CorbaException) = 0;
  virtual void _leave(const string &id) throw(CorbaException) = 0;

  string                  _name;
  string                  _description;
  RolePlaying::System_var _system;
  unsigned int            game_type;

private:
  virtual char *name() throw(CORBA::Exception);
  virtual char *description() throw(CORBA::Exception);
  virtual RolePlaying::System_ptr system_o() throw(CORBA::Exception);
  virtual GameType type() throw(CORBA::Exception);
  virtual char *join(RolePlaying::Client_ptr cl)
    throw(CORBA::Exception);
  virtual void leave(const char *id) throw(CORBA::Exception);
};

#endif // GAME_IMPL_HH
