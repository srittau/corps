/*  RolePlaying::System implementation
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

#include <cstring>

#include <i18n.hh>

#include "corbaexception.hh"
#include "system-impl.hh"


System_Impl::System_Impl() throw() :
  _name(_("Unnamed")),
  _description(_("No description was provided by the system's author."))
{
}


System_Impl::~System_Impl() throw()
{
}


char *System_Impl::name() throw(CORBA::Exception)
{
  try
    {
      const string &n = get_name();
      char *ret = CORBA::string_alloc(n.size());
      if(!ret)
        throw CORBA::NO_MEMORY();
      strcpy(ret, n.c_str());
      return ret;
    }
  catch(CorbaException e) { e.raise(); }
  catch(CORBA::Exception e) { throw e; }
  catch(...) { throw CORBA::UNKNOWN(); }
}


string System_Impl::get_name() throw(CorbaException)
{
  return _name;
}


string System_Impl::get_description() throw(CorbaException)
{
  return _description;
}


char *System_Impl::description() throw(CORBA::Exception)
{
  try
    {
      const string &d = get_description();
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
