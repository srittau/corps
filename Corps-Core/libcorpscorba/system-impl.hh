#ifndef SYSTEM_IMPL_HH
#define SYSTEM_IMPL_HH

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

#include <string>

#include "roleplaying.hh"


class CorbaException;


class System_Impl : public RolePlaying::_sk_System
{
public:
  System_Impl() throw();
  virtual ~System_Impl() throw();

protected:
  virtual string get_name() throw(CorbaException);
  virtual string get_description() throw(CorbaException);

  string _name;
  string _description;

private:
  virtual char *name() throw(CORBA::Exception);
  virtual char *description() throw(CORBA::Exception);
};

#endif // SYSTEM_IMPL_HH
