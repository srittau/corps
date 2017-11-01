/*  CORBA support class for CORPS
    Copyright (C) 1999-2000 Sebastian Rittau

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

#include <libintl.h>

#include <omniORB2/CORBA.h>

#include "corbaexception.hh"
#include "exception.hh"
#include "orb.hh"


CORPS_ORB *orb = 0;


CORPS_ORB::CORPS_ORB(int argc, char *argv[]) throw(Exception)
{
  try
    {
      /* Initialize ORB */
      orb = CORBA::ORB_init(argc, argv, "omniORB2");

      /* Initialize BOA */
      boa = orb->BOA_init(argc, argv, "omniORB2_BOA");
    }
  catch(CORBA::SystemException e)
    {
      throw Exception(gettext("could not initialize CORBA"));
    }
}


CORPS_ORB::~CORPS_ORB() throw()
{
  boa->destroy();
  orb->NP_destroy();
}


void CORPS_ORB::ready() throw()
{
  boa->impl_is_ready(0, 1);
}


void CORPS_ORB::run() throw()
{
  boa->impl_is_ready();
}


void CORPS_ORB::shutdown() throw()
{
  boa->impl_shutdown();
}


string CORPS_ORB::object_to_string(CORBA::Object_ptr o) const
  throw(CorbaException)
{
  char *retval;
  try { retval = orb->object_to_string(o); }
  catch(CORBA::SystemException e) { throw CorbaException(e); }
  string str(retval);
  CORBA::string_free(retval);
  return str;
}


CORBA::Object_var CORPS_ORB::string_to_object(const string &id) const
  throw(CorbaException)
{
  CORBA::Object_var o;
  try { o = orb->string_to_object(id.c_str()); }
  catch(CORBA::SystemException e) { throw CorbaException(e); }
  return o;
}


CORBA::Context_var CORPS_ORB::get_context() throw(CorbaException)
{
  CORBA::Context_var out;
  orb->get_default_context(out);
  return out;
}
