#ifndef CLIENTTEXT_IMPL_HH
#define CLIENTTEXT_IMPL_HH

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

class Client_GUI;


class ClientText_Impl : public virtual RolePlaying::_sk_MIMEHandlerText
{
public:
  ClientText_Impl(Client_GUI &g) throw();
  virtual ~ClientText_Impl() throw() {}

  // RolePlaying::MIMEHandlerBase
  virtual char *Type() throw(CORBA::NO_MEMORY);

  // RolePlaying::MIMEHandlerText
  virtual void print(const char *text) throw(RolePlaying::WrongCookie);
  virtual void request_string (const char *what, char *&str) throw(RolePlaying::WrongCookie, CORBA::NO_MEMORY);
  virtual void request_text (const char *what, char *&text) throw(RolePlaying::WrongCookie, CORBA::NO_MEMORY);

private:
  Client_GUI &c_gui;
};

#endif // CLIENTTEXT_IMPL_HH
