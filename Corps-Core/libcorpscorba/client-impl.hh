#ifndef CLIENT_IMPL_HH
#define CLIENT_IMPL_HH

/*  RolePlaying::Client implementation
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
#include <vector>

#include "clienthandler-impl.hh"
#include "roleplaying.hh"


class CorbaException;
class Exception;


class Client_Impl : public virtual RolePlaying::_sk_Client
{
public:
  Client_Impl() throw();
  virtual ~Client_Impl() throw();

  // Add a new handler to the list of handlers, possibly replacing an
  // old handler of the same type.
  void add_handler(const string &which,
		   RolePlaying::ClientHandler_var handler) throw();
  // Remove a handler from the list of handlers. Throws exception
  // NO_SUCH_HANDLER if there is no such handler.
  void remove_handler(const string &which) throw(Exception);

protected:
  // The default method returns handlers that were registered with
  // add_handler(). You may of course override this method with your
  // own version.
  virtual RolePlaying::ClientHandler_var _get_handler(const string &which,
						      unsigned long version)
    throw(CorbaException);
  // kick() is defined "oneway" so there is no point in throwing
  // exceptions.
  virtual void _kick(const string &reason) throw(CorbaException) = 0;
  // The default method always throws exception UnknownMIMEType.
  virtual void _request_object(const string &type, CORBA::Object_ptr &o)
    throw(CorbaException);

private:
  // CORBA methods
  virtual RolePlaying::ClientHandler_ptr get_handler(const char *which,
						     CORBA::ULong version)
    throw(CORBA::Exception);
  virtual void kick(const char *reason, CORBA::Context *ctx)
    throw(CORBA::Exception);
  virtual void request_object(const char *type, CORBA::Object_ptr &o,
			      CORBA::Context *ctx)
    throw(CORBA::Exception);

  typedef struct { string type; RolePlaying::ClientHandler_var o; }
    ClientHandler_Entry;
  vector<ClientHandler_Entry> handler_list;
};

#endif // CLIENT_IMPL_HH
