/*  image/* MIME Type implementation
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

#include "clientimage-impl.hh"

class Client_GUI;


ClientImage_Impl::ClientImage_Impl(Client_GUI &g) throw() :
  _sk_MIMEHandlerImage(),

  gui(g)
{
}


RolePlaying::MIMEType ClientImage_Impl::Type() throw(CORBA::NO_MEMORY)
{
  char *ret = CORBA::string_dup("image/*");
  if(!ret)
    throw CORBA::NO_MEMORY();
  return ret;
}


void ClientImage_Impl::display(const Image & img) throw(CORBA::SystemException)
{
  //FIXME
}
