#ifndef CLIENTHANDLER_WRAPPER_HH
#define CLIENTHANDLER_WRAPPER_HH

/*  Interface for ClientHandler-Wrapper
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

#include "roleplaying.hh"

class CorbaException;


class ClientHandler_Wrapper
{
public:
  ClientHandler_Wrapper(const RolePlaying::ClientHandler_var &obj,
			CORBA::Context_ptr ctx)
    throw(CorbaException);

  operator RolePlaying::ClientHandler_var &() throw()
  { return clienthandler; }
  operator const RolePlaying::ClientHandler_var &() const throw()
  { return clienthandler; }

  // CORBA methods
  void enable() throw(CorbaException);
  void disable() throw(CorbaException);

protected:
  CORBA::Context_var context;

private:
  RolePlaying::ClientHandler_var clienthandler;
};

#endif // CLIENTHANDLER_WRAPPER_HH
