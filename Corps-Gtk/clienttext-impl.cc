/*  Text MIME Type implementation
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

#include <corps/roleplaying.hh>

#include "client-gui.hh"
#include "clienttext-impl.hh"


ClientText_Impl::ClientText_Impl(Client_GUI &g) throw() :
  _sk_MIMEHandlerText(),

  c_gui(g)
{
}


RolePlaying::MIMEType ClientText_Impl::Type() throw(CORBA::NO_MEMORY)
{
  char *ret = CORBA::string_dup("text/plain");
  if(!ret)
    throw CORBA::NO_MEMORY();
  return ret;
}


void ClientText_Impl::print(const char *text) throw(RolePlaying::WrongCookie)
{
#if 0 //FIXME
  if(!cl.is_correct_context(0)) //FIXME
    throw RolePlaying::WrongCookie();
#endif

  c_gui.print_text(text);
}


void ClientText_Impl::request_string (const char *what, char *&str)
  throw(RolePlaying::WrongCookie, CORBA::NO_MEMORY)
{
#if 0 // FIXME
  if(!cl.is_correct_context(0)) //FIXME
    throw RolePlaying::WrongCookie();
#endif

  string s(c_gui.request_string(what));
  str = CORBA::string_dup(s.c_str());
  if(!str)
    throw CORBA::NO_MEMORY();
}


void ClientText_Impl::request_text(const char *what, char *&text)
  throw(RolePlaying::WrongCookie, CORBA::NO_MEMORY)
{
#if 0 //FIXME
  if(!cl.is_correct_context(0)) //FIXME
    throw RolePlaying::WrongCookie();
#endif

  string s(c_gui.request_text(what));
  text = CORBA::string_dup(s.c_str());
  if(!text)
    throw CORBA::NO_MEMORY();
}
