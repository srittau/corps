/*  Wrapper for CORPS interface RolePlaying::Client
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

#include "client-wrapper.hh"
#include "clienthandler-wrapper.hh"
#include "corbaexception.hh"
#include "orb.hh"
#include "tools.hh"


extern CORPS_ORB *orb;


Client_Wrapper::Client_Wrapper() throw() :
  client(RolePlaying::Client::_nil()),
  context(orb->get_context()),
  cookie(create_cookie())
{
  CORBA::Any any;
  any <<= cookie.c_str();
  context->set_one_value("cookie", any);
}


Client_Wrapper::Client_Wrapper(const RolePlaying::Client_var &o)
  throw(CorbaException) :
  client(o),
  context(orb->get_context()),
  cookie(create_cookie())
{
  CORBA::Any any;
  any <<= cookie.c_str();
  context->set_one_value("cookie", any);
}


Client_Wrapper &Client_Wrapper::operator=(const RolePlaying::Client_var &co)
  throw(CorbaException)
{
  client = co;
  context = orb->get_context();
  cookie = create_cookie();

  return *this;
}


bool Client_Wrapper::operator==(const Client_Wrapper &o) throw()
{
  return client->_is_equivalent(o.client);
}


ClientHandler_Wrapper Client_Wrapper::get_handler(const string &which,
						  unsigned int version)
  throw(CorbaException)
{
  try
    {
      RolePlaying::ClientHandler_ptr ch =
	client->get_handler(which.c_str(),
			    static_cast<CORBA::ULong>(version));
      ClientHandler_Wrapper handler(ch, context);
      // ClientHandler_Wrapper assumes ownership of ch
    }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}


void Client_Wrapper::kick(const string &reason) throw(CorbaException)
{
  try { client->kick(reason.c_str(), context); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}


void Client_Wrapper::request_object(const string &type, CORBA::Object_ptr o)
  throw(CorbaException)
{
  try { client->_0RL__request_object(type.c_str(), o, context); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}
