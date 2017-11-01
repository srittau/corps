/*  CORBA Utility functions
    Copyright (C) 1998-2000 Sebastian Rittau

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
#include <string>
#include <cstdio>

#include <pthread.h>
#include <libintl.h>

#include "exception.hh"
#include "tools.hh"


// just for testing for corps-core
char corps_core()
{
}

/************************************************************************/

//FIXME
#include <ctime>
string create_cookie() throw()
{
  time_t t = time(0);
  return ctime(&t);
}

/************************************************************************/

void threaded_output(const string &str) throw()
{
  cout << "(" << pthread_self() << ") " << str << endl;
}


void threaded_warning(const string &str) throw()
{
  char thread_id[12];
  sprintf(thread_id, "%d", pthread_self());
  string new_str = string("(") + thread_id + ") " + str;
  Exception(new_str).print_warning(false);
}


string insert_text(const string &text, const string &insert) throw()
{
  string new_text(text);
  return insert_text(new_text, insert);
}


string insert_text(string &text, const string &insert) throw()
{
  string::size_type pos = text.find("%s");
  if(pos != string::npos)
    text.replace(pos, 2, insert);
  return text;
}
