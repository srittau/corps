#ifndef CLIENT_HH
#define CLIENT_HH

/*  A simple CORPS client (for corps-client)
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

#include <corps/client-impl.hh>


class Client : public Client_Impl
{
public:
  Client() throw();
  virtual ~Client() throw() {}

  virtual void _kick(const string &reason) throw();
};

#endif // CLIENT_IMPL_HH
