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

#include "client-impl.hh"
#include "corbaexception.hh"
#include "roleplaying.hh"


//FIXME: list protected with mutex
Client_Impl::Client_Impl() throw() :
  handler_list()
{
}


Client_Impl::~Client_Impl() throw()
{
}


void Client_Impl::add_handler(const string &which,
			      const RolePlaying::ClientHandler_var handler)
  throw()
{
  // Possibly remove handler if handler of type which does already exist.
  try { remove_handler(which); }
  catch(...) {}

  ClientHandler_Entry e = { which, handler };
  handler_list.insert(handler_list.end(), e);
}


void Client_Impl::remove_handler(const string &which) throw(Exception)
{
  vector<ClientHandler_Entry>::size_type pos = 0;
  while(pos < handler_list.size())
    {
      if(handler_list[pos].type == which)
	{
	  handler_list.erase(&handler_list[pos]);
	  return;
	}
      pos++;
    }

  throw Exception(Exception::NO_SUCH_OBJECT);
}


RolePlaying::ClientHandler_var Client_Impl::_get_handler(const string &which,
							 unsigned long version)
  throw(CorbaException)
{
  vector<ClientHandler_Entry>::size_type pos = 0;
  while(pos < handler_list.size())
    {
      if(handler_list[pos].type == which)
	return handler_list[pos].o;
      pos++;
    }

  throw CorbaException(RolePlaying::ClientHandler::NoSuchHandler());
}


void Client_Impl::_request_object(const string &type, CORBA::Object_ptr &o)
  throw(CorbaException)
{
  throw CorbaException(RolePlaying::UnknownMIMEType(type.c_str()));
}

///////////////////////////// CORBA methods //////////////////////////////

RolePlaying::ClientHandler_ptr
Client_Impl::get_handler(const char *which, CORBA::ULong version)
  throw(CORBA::Exception)
{
  try { return _get_handler(which, static_cast<unsigned int>(version)); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}


void Client_Impl::kick(const char *reason, CORBA::Context *ctx)
  throw(CORBA::Exception)
{
  // FIXME: cookie handling
  try { _kick(reason); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}


void Client_Impl::request_object(const char *type, CORBA::Object_ptr &o,
				 CORBA::Context *ctx)
  throw(CORBA::Exception)
{
  // FIXME: cookie handling
  try { _request_object(type, o); }
  catch(CorbaException e) { e.raise(); }
  catch(...) { throw CORBA::UNKNOWN(); }
}
