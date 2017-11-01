#ifndef CLIENT_WRAPPER_HH
#define CLIENT_WRAPPER_HH

/*  Interface for Client-Wrapper
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

class ClientHandler_Wrapper;
class CorbaException;


class Client_Wrapper
{
public:
  Client_Wrapper() throw();
  Client_Wrapper(const RolePlaying::Client_var &obj) throw(CorbaException);

  Client_Wrapper &operator=(const RolePlaying::Client_var &co)
    throw(CorbaException);
  bool operator==(const Client_Wrapper &o) throw();

  operator RolePlaying::Client_var &() throw() { return client; }
  operator const RolePlaying::Client_var &() const throw() { return client; }

  // CORBA methods
  ClientHandler_Wrapper get_handler(const string &which, unsigned int version)
    throw(CorbaException);
  void kick(const string &reason) throw(CorbaException);
  void request_object(const string &type, CORBA::Object_ptr o)
    throw(CorbaException);

  // support methods
  const string &get_cookie() const throw() { return cookie; }

private:
  RolePlaying::Client_var client;

  CORBA::Context_var context;
  string cookie;
};

#endif // CLIENT_WRAPPER_HH
