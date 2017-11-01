#ifndef __ORB_HH
#define __ORB_HH

/*  Interface for class CORPS_ORB
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

#include <omniORB2/CORBA.h>


class CorbaException;
class Exception;


class CORPS_ORB
{
public:
  CORPS_ORB(int argc, char *argv[]) throw(Exception);
  ~CORPS_ORB() throw();

  void ready() throw(); // non-blocking
  void run() throw(); // blocking

  string object_to_string(CORBA::Object_ptr o) const throw(CorbaException);
  CORBA::Object_var string_to_object(const string &id) const
    throw(CorbaException);

  void shutdown() throw();

  CORBA::ORB_var getORB() throw() { return orb; }
  const CORBA::ORB_var getORB() const throw() { return orb; }
  CORBA::BOA_var getBOA() throw() { return boa; }
  const CORBA::BOA_var getBOA() const throw() { return boa; }

  CORBA::Context_var get_context() throw(CorbaException);

private:
  CORBA::ORB_var orb;
  CORBA::BOA_var boa;
};

#endif // __ORB_HH
