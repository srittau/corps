#ifndef CHARACTER_IMPL_HH
#define CHARACTER_IMPL_HH

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

#include <string>

#include <pthread.h>

#include "property-impl.hh"
#include "roleplaying.hh"
#include "thing-impl.hh"


class Character_Impl : public virtual RolePlaying::_sk_Character
{
public:
  Character_Impl() throw();
  virtual ~Character_Impl() throw();

  // CORBA methods
  virtual char *Name() throw(CORBA::NO_MEMORY);
  virtual RolePlaying::PropertyList *Properties() throw();
  virtual RolePlaying::ThingList *Inventory() throw();

protected:
  // every attribute is protected by its own lock - use them when changing
  // an attribute during CORBA object lifetime
  string char_name;
  pthread_mutex_t char_name_lock;
  PropList prop_list;
  pthread_mutex_t prop_list_lock;
  ThList inventory;
  pthread_mutex_t inventory_lock;
};

#endif // CHARACTER_IMPL_HH
