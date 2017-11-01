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

#include <iostream>

#include <omniORB2/CORBA.h>

#include "corbaexception.hh"
#include "gamelist-impl.hh"


GameList_Impl::GameList_Impl() throw() :
  _sk_GameList()
{
}


GameList_Impl::~GameList_Impl() throw()
{
}


RolePlaying::GameList::GList *GameList_Impl::list() throw(CORBA::Exception)
{
  try
    {
      ::GameList list = get_list();

      GList *new_list = new GList(list.size());
      new_list->length(list.size());

      ::GameList::size_type pos = 0;
      while(pos < list.size())
	{
	  (*new_list)[pos] =
	    RolePlaying::Game::_duplicate((RolePlaying::Game_var &)list[pos]);
	  pos++;
	}

      return new_list;
    }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}


#include <cstdio> //FIXME
char *GameList_Impl::_cxx_register(RolePlaying::Game_ptr g)
  throw(CORBA::Exception)
{
  try
    {
      string id = _register(Game_Wrapper(g));
      char *ret = CORBA::string_alloc(id.size());
      if(!ret)
	throw CORBA::NO_MEMORY();
      strcpy(ret, id.c_str());
      return ret;
    }
  catch(CorbaException e) { printf("blubb\n"); e.raise(); } //FIXME
  catch(CORBA::Exception e) { throw e; }
  catch(...) { throw CORBA::UNKNOWN(); }
}


// Since this method is flagged "oneway" there is no point in throwing
// exceptions.
void GameList_Impl::unregister(const char *id) throw(CORBA::Exception)
{
  try { string new_id(id); _unregister(new_id); }
  catch(...) {}
}
