/*  Client implementation for GCorps
    Copyright (C) 1998-99 Sebastian Rittau

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

#include "client.hh"
#include "client-i.hh"


Client_I::Client_I(::Client &parent) throw(Exception) :
  Client_Impl(),

  client(parent)
{
#if 0 //FIXME
  // initialize mime-lists
  input_list = new MIMEList_Impl;
  input_list->insert(input_list->end(), "text/plain");
  input_list->insert(input_list->end(), "image/gif");
  input_list->insert(input_list->end(), "image/jpg");
  input_list->insert(input_list->end(), "image/png");
  input_list->insert(input_list->end(), "x-rpg/map");
  input_list->_obj_is_ready(comm->getCORBABOA());
  output_list = new MIMEList_Impl;
  output_list->insert(output_list->end(), "text/plain");
  output_list->_obj_is_ready(comm->getCORBABOA());

  text_o = new ClientText_Impl(client.getGUI());
  text_o->_obj_is_ready(comm->getCORBABOA());
  image_o = new ClientImage_Impl(client.getGUI());
  image_o->_obj_is_ready(comm->getCORBABOA());
  x_rpg_map_o = new ClientMap_Impl(client.getGUI());
  x_rpg_map_o->_obj_is_ready(comm->getCORBABOA());
#endif
}


Client_I::~Client_I() throw()
{
}


#if 0 //FIXME
RolePlaying::MIMEHandlerBase_ptr Client_Impl::get_MIMEObject(const char *which)
  throw(CORBA::SystemException, MIMETypeNotSupported)
{
  if(!strcasecmp(which, "text/plain"))
    return RolePlaying::MIMEHandlerText::_duplicate(text_o);
  else if(!strncasecmp(which, "image/", 6))
    return RolePlaying::MIMEHandlerImage::_duplicate(image_o);
  else if(!strcasecmp(which, "x-rpg/map"))
    return RolePlaying::MIMEHandlerMap::_duplicate(x_rpg_map_o);
  else
    throw MIMETypeNotSupported();
}
#endif


void Client_I::_kick(const string &reason) throw(CorbaException)
{
  try { client.kick(reason); }
  catch(...) {}
}
