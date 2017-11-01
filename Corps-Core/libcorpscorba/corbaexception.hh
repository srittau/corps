#ifndef CORBAEXCEPTION_H
#define CORBAEXCEPTION_H

/*  Interface definition for CORBA exception handling class
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

#include <omniORB2/CORBA.h>

#include "exception.hh"


class CorbaException : public ::Exception, public CORBA::Exception {
public:
  CorbaException() throw();
  CorbaException(const CORBA::Exception &e) throw();

  CorbaException &operator=(const CORBA::Exception &e) throw();

  void set(const CORBA::Exception &e) throw();

  void raise() throw(CORBA::Exception);
};

#endif // CORBAEXCEPTION_HH
