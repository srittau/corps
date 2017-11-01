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

#include <iostream>

#include <pthread.h>

#include <corps/roleplaying.hh>

#include "client-impl.hh"
#include "clienttext-impl.hh"


extern pthread_mutex_t stdin_lock;


ClientText_Impl::ClientText_Impl(Client_Impl &parent) throw() :
  _sk_MIMEHandlerText(),

  cl(parent)
{
  pthread_mutex_init(&stdin_lock, 0);
}


ClientText_Impl::~ClientText_Impl() throw()
{
  pthread_mutex_destroy(&stdin_lock);
}


char *ClientText_Impl::Type() throw(CORBA::NO_MEMORY)
{
  char *ret = CORBA::string_dup("text/plain");
  if(!ret)
    throw CORBA::NO_MEMORY();
  return ret;
}


void ClientText_Impl::print(const char* text)
  throw(RolePlaying::WrongCookie)
{
  if(!cl.is_correct_context(0))
    throw RolePlaying::WrongCookie();

  cout << text << endl;
}


void ClientText_Impl::request_string(const char *what, char *&str)
  throw(RolePlaying::WrongCookie)
{
  if(!cl.is_correct_context(0))
    throw RolePlaying::WrongCookie();

  pthread_mutex_lock(&stdin_lock);

  cout << what << endl << "? ";
  cout.flush();

  const int line_buffer_size = 80;
  char buffer[line_buffer_size];
  cin.getline(buffer, line_buffer_size, '\n');
  str = CORBA::string_dup(buffer);

  pthread_mutex_unlock(&stdin_lock);
}


void ClientText_Impl::request_text(const char *what, char *&text)
  throw(RolePlaying::WrongCookie)
{
  if(!cl.is_correct_context(0))
    throw RolePlaying::WrongCookie();

  pthread_mutex_lock(&stdin_lock);

  cout << what << endl << "? ";
  cout.flush();

  const int line_buffer_size = 16384; //FIXME: variable length
  char buffer[line_buffer_size];
  cin.getline(buffer, line_buffer_size, '\n');
  text = CORBA::string_dup(buffer);

  pthread_mutex_unlock(&stdin_lock);
}
