/*  Wrapper for CORPS interface RolePlaying::ClientHandler
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

#include "clienthandler-wrapper.hh"
#include "corbaexception.hh"


ClientHandler_Wrapper::ClientHandler_Wrapper(
  const RolePlaying::ClientHandler_var &o, CORBA::Context_ptr ctx
) throw(CorbaException) :
  context(ctx),
  clienthandler(o)
{
}


void ClientHandler_Wrapper::enable() throw(CorbaException)
{
  try { clienthandler->enable(); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}


void ClientHandler_Wrapper::disable() throw(CorbaException)
{
  try { clienthandler->disable(); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}
