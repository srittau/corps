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

#include "ch-history-wrapper.hh"
#include "corbaexception.hh"


CH_History_Wrapper::CH_History_Wrapper(const ClientHandler_Wrapper &o)
  throw(CorbaException) :
  ClientHandler_Wrapper(o)
{
}


void CH_History_Wrapper::append_text(const string &text)
  throw(CorbaException)
{
  try { ch_history->append_text(text.c_str(), context); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}


void CH_History_Wrapper::clear() throw(CorbaException)
{
  try { ch_history->clear(context); }
  catch(CORBA::Exception e) { throw CorbaException(e); }
}
