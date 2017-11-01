/*  Wrapper for CORPA interface RolePlaying::System
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

#include "corbaexception.hh"
#include "exception.hh"
#include "system-wrapper.hh"


System_Wrapper::System_Wrapper() throw() :
  system(RolePlaying::System::_nil()),

  name(),
  description()
{
}


System_Wrapper::System_Wrapper(const RolePlaying::System_var &so)
  throw(Exception) :
  system(so),

  name(),
  description()
{
  if(!RolePlaying::System::_narrow(system))
    throw Exception(Exception::INTERNAL_ERROR);
  attrs_from_object();
}


System_Wrapper &System_Wrapper::operator=(const RolePlaying::System_var &so)
  throw(CorbaException)
{
  system = so;

  attrs_from_object();

  return *this;
}


bool System_Wrapper::operator==(const System_Wrapper &o) throw()
{
  return system->_is_equivalent(o.system);
}


void System_Wrapper::attrs_from_object() throw(CorbaException)
{
  try
    {
      char *str;

      // get game name
      str = system->name();
      name.assign(str);
      CORBA::string_free(str);

      // get game description
      str = system->description();
      description.assign(str);
      CORBA::string_free(str);
    }
  catch(CorbaException e) { throw e; }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}
