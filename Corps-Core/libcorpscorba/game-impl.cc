/*  RolePlaying::Game implementation
    Copyright (C) 1999-2000 Sebastian Rittau

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

#include <cstring>

#include <i18n.hh>

#include "client-wrapper.hh"
#include "corbaexception.hh"
#include "game-impl.hh"


Game_Impl::Game_Impl(const RolePlaying::System_var &s) throw() :
  _name(_("Unnamed")),
  _description(_("The game´s author did not provide a description.")),
  _system(s),
  game_type(0)
{
}


#include <cstdio> //FIXME
char *Game_Impl::name() throw(CORBA::Exception)
{
  printf("Game_Impl: name() entered\n"); //FIXME
  try
    {
      string n = get_name();
      char *ret = CORBA::string_alloc(n.size());
      if(!ret)
        throw CORBA::NO_MEMORY();
      strcpy(ret, n.c_str());
      printf("left Game_Impl::name()\n"); //FIXME

      return ret;
    }
  catch(CorbaException e) { e.raise(); }
  catch(CORBA::Exception e) { throw e; }
  catch(...) { throw CORBA::UNKNOWN(); }
}


char *Game_Impl::description() throw(CORBA::Exception)
{
  try
    {
      string d = get_description();
      char *ret = CORBA::string_alloc(d.size());
      if(!ret)
        throw CORBA::NO_MEMORY();
      strcpy(ret, d.c_str());
      return ret;
    }
  catch(CorbaException e) { e.raise(); }
  catch(CORBA::Exception e) { throw e; }
  catch(...) { throw CORBA::UNKNOWN(); }
}


RolePlaying::System_ptr Game_Impl::system_o() throw(CORBA::Exception)
{
  try { return RolePlaying::System::_duplicate(get_system_o()); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}


RolePlaying::Game::GameType Game_Impl::type() throw(CORBA::Exception)
{
  try { return static_cast<GameType>(get_type()); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}


#include <iostream> //FIXME
char *Game_Impl::join(RolePlaying::Client_ptr cl)
  throw(CORBA::Exception)
{
  cerr << "Game_Impl: at the beginning of join\n"; //FIXME
  try
    {

      Client_Wrapper cl_wrapper(cl);

      string id = _join(cl_wrapper);
      char *ret = CORBA::string_alloc(id.size());
      if(!ret)
        throw CORBA::NO_MEMORY();
      strcpy(ret, id.c_str());
cout << "Game_Impl: before returning from join\n"; //FIXME
      return ret;

    }
  catch(CorbaException e) { cout << "Game_Impl: CorbaException\n"; e.raise(); } //FIXME
  catch(CORBA::Exception e) { cout << "Game_Impl: CORBA::Exception\n"; throw e; } //FIXME
  catch(...) { cout << "Game_Impl: other exception\n"; throw CORBA::UNKNOWN(); }//FIXME
}


void Game_Impl::leave(const char *id) throw(CORBA::Exception)
{
  try { _leave(id); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}
