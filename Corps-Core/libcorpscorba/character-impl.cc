/*  RolePlaying::Character implementation
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

#include "character-impl.hh"


Character_Impl::Character_Impl() throw() :
  char_name(),
  prop_list(),
  inventory()
{
  pthread_mutex_init(&char_name_lock, 0);
  pthread_mutex_init(&prop_list_lock, 0);
  pthread_mutex_init(&inventory_lock, 0);
}


Character_Impl::~Character_Impl() throw()
{
  pthread_mutex_destroy(&char_name_lock);
  pthread_mutex_destroy(&prop_list_lock);
  pthread_mutex_destroy(&inventory_lock);
}


char *Character_Impl::Name() throw(CORBA::NO_MEMORY)
{
  pthread_mutex_lock(&char_name_lock);

  char *name = CORBA::string_dup(char_name.c_str());

  pthread_mutex_unlock(&char_name_lock);

  if(!name)
    throw CORBA::NO_MEMORY();
  return name;
}


RolePlaying::PropertyList *Character_Impl::Properties() throw()
{
  pthread_mutex_lock(&prop_list_lock);

  RolePlaying::PropertyList *list = new RolePlaying::PropertyList(prop_list.size());
  list->length(prop_list.size());
  //FIXME: copy list

  pthread_mutex_unlock(&prop_list_lock);
  return list;
}


RolePlaying::ThingList *Character_Impl::Inventory() throw()
{
  pthread_mutex_lock(&inventory_lock);

  RolePlaying::ThingList *list = new RolePlaying::ThingList(inventory.size());
  list->length(inventory.size());
  //FIXME: copy list

  pthread_mutex_unlock(&inventory_lock);
  return list;
}
