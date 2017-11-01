/*  RolePlaying::Thing implementation
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

#include "thing-impl.hh"


Thing_Impl::Thing_Impl() throw() :
  thing_name(),
  prop_list()
{
  pthread_mutex_init(&thing_name_lock, 0);
  pthread_mutex_init(&prop_list_lock, 0);
}


Thing_Impl::~Thing_Impl() throw()
{
  pthread_mutex_destroy(&thing_name_lock);
  pthread_mutex_destroy(&prop_list_lock);
}


char *Thing_Impl::Name() throw(CORBA::NO_MEMORY)
{
  pthread_mutex_lock(&thing_name_lock);

  char *name = CORBA::string_dup(thing_name.c_str());

  pthread_mutex_lock(&thing_name_lock);

  if(!name)
    throw CORBA::NO_MEMORY();
  return name;
}


RolePlaying::PropertyList *Thing_Impl::Properties() throw()
{
  pthread_mutex_lock(&prop_list_lock);

  RolePlaying::PropertyList *list = new RolePlaying::PropertyList(prop_list.size());
  list->length(prop_list.size());
  //FIXME: copy list

  pthread_mutex_unlock(&prop_list_lock);
  return list;
}
