/*  RolePlaying::Property implementation
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

#include "property-impl.hh"


Property_Impl::Property_Impl() throw() :
  mime(),
  type()
{
  pthread_mutex_init(&mime_lock, 0);
  pthread_mutex_init(&type_lock, 0);
}


Property_Impl::~Property_Impl() throw()
{
  pthread_mutex_destroy(&mime_lock);
  pthread_mutex_destroy(&type_lock);
}


char *Property_Impl::Medium() throw(CORBA::NO_MEMORY)
{
  pthread_mutex_lock(&mime_lock);

  char *m = CORBA::string_dup(mime.c_str());

  pthread_mutex_unlock(&mime_lock);

  if(!m)
    throw CORBA::NO_MEMORY();
  return m;
}


char *Property_Impl::id() throw(CORBA::NO_MEMORY)
{
  pthread_mutex_lock(&type_lock);

  char *t = CORBA::string_dup(type.c_str());

  pthread_mutex_unlock(&type_lock);

  if(!t)
    throw CORBA::NO_MEMORY();
  return t;
}


CORBA::Object_ptr Property_Impl::Data() throw()
{
  //FIXME
}
