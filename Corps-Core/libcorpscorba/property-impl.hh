#ifndef PROPERTY_IMPL_HH
#define PROPERTY_IMPL_HH

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

#include <string>
#include <vector>

#include <pthread.h>

#include "roleplaying.hh"


class Property_Impl : public virtual RolePlaying::_sk_Property
{
public:
  Property_Impl() throw();
  virtual ~Property_Impl() throw();

  // CORBA methods
  virtual char *Medium() throw(CORBA::NO_MEMORY);
  virtual char *id() throw(CORBA::NO_MEMORY);
  virtual CORBA::Object_ptr Data() throw();

protected:
  string mime;
  pthread_mutex_t mime_lock;
  string type;
  pthread_mutex_t type_lock;
};

typedef vector<Property_Impl> PropList;

#endif // PROPERTY_IMPL_HH
