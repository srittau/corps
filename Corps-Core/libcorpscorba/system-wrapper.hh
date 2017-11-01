#ifndef SYSTEM_WRAPPER_HH
#define SYSTEM_WRAPPER_HH

/*  Interface for System-Wrapper
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

#include <string>

#include "roleplaying.hh"

class CorbaException;
class Exception;


class System_Wrapper
{
public:
  System_Wrapper() throw();
  System_Wrapper(const RolePlaying::System_var &so) throw(Exception);

  System_Wrapper &operator=(const RolePlaying::System_var &go) throw(CorbaException);
  bool operator==(const System_Wrapper &o) throw();

  operator RolePlaying::System_var &() throw() { return system; }
  operator const RolePlaying::System_var &() const throw() { return system; }

  const string &get_name() const throw() { return name; }
  const string &get_description() const throw() { return description; }

private:
  void attrs_from_object() throw(CorbaException);

  RolePlaying::System_var system;

  string name;
  string description;
};

#endif // SYSTEM_WRAPPER_HH
