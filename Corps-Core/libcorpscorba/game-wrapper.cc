/*  Wrapper for CORPA interface RolePlaying::Game
    Copyright (C) 1998-2000 Sebastian Rittau

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

#include <libintl.h>

#include "corbaexception.hh"
#include "exception.hh"
#include "game-wrapper.hh"


Game_Wrapper::Game_Wrapper() throw() :
  game(RolePlaying::Game::_nil()),

  name(),
  description(),
  system(),
  type(0),

  cookie()
{
}


Game_Wrapper::Game_Wrapper(const RolePlaying::Game_var &go)
  throw(CorbaException) :
  game(go),

  name(),
  description(),
  system(),
  type(0),

  cookie()
{
  attrs_from_object();
}


Game_Wrapper &Game_Wrapper::operator=(const RolePlaying::Game_var &go)
  throw(CorbaException)
{
  game = go;

  attrs_from_object();

  return *this;
}


bool Game_Wrapper::operator==(const Game_Wrapper &o) throw()
{
  return game->_is_equivalent(o.game);
}


const string &Game_Wrapper::join(RolePlaying::Client_ptr cl)
  throw(Exception)
{
  if(CORBA::is_nil(game))
    throw Exception(Exception::INTERNAL_ERROR);

  // connect and handle return
  try
    {
      char *id = game->join(cl);
      cookie = id;
      CORBA::string_free(id);
    }
  catch(RolePlaying::Game::FeatureMissing e)
    { throw Exception(gettext("This client does not support all needed features.")); }
  catch(RolePlaying::Game::GameFull e)
    { throw Exception(gettext("The game does not accept more clients.")); }
  catch(RolePlaying::Game::NoAuthorization e)
    { throw Exception(gettext("You are not authorized to join this game.")); }
  catch(RolePlaying::Game::AlreadyJoined e)
    { throw Exception(gettext("You are always connected to this game.")); }
  catch(CORBA::SystemException e)
    { throw CorbaException(e); }

  return cookie;
}


void Game_Wrapper::leave() throw(Exception)
{
  if(CORBA::is_nil(game))
    throw Exception(Exception::INTERNAL_ERROR);

  game->leave(cookie.c_str());
}


void Game_Wrapper::leave(const string &id) throw(Exception)
{
  if(CORBA::is_nil(game))
    throw Exception(Exception::INTERNAL_ERROR);

  game->leave(id.c_str());
}


#include <cstdio> //FIXME
void Game_Wrapper::attrs_from_object() throw(CorbaException)
{
  try
    {
      char *str;

      // get game name
      printf("Game_Wrapper: before asking game for its name\n"); //FIXME
      str = game->name();
      printf("Game_Wrapper: after asking game for its name\n"); //FIXME
      name.assign(str);
      CORBA::string_free(str);

      // get game description
      str = game->description();
      description.assign(str);
      CORBA::string_free(str);

      // get game type
      type = game->type();

      RolePlaying::System_ptr sys_var(game->system_o());
      printf("Game_Wrapper: before creating System_Wrapper\n"); //FIXME
      system = System_Wrapper(sys_var);
      printf("Game_Wrapper: after creating System_Wrapper\n"); //FIXME
    }
  catch(CorbaException e) { printf("Game_Wrapper: Exception: CorbaException\n"); throw e; } //FIXME
  catch(CORBA::SystemException e) { printf("Game_Wrapper: Exception: CORBA::Exception: %s\n", e.NP_RepositoryId()); throw CorbaException(e); } //FIXME: SystemE -> E
}
