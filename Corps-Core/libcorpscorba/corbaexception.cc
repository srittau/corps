/*  Interface definition for CORBA exception handling class
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

#include <libintl.h>

#include <omniORB2/CORBA.h>

#include "corbaexception.hh"
#include "i18n.hh"
#include "tools.hh"


CorbaException::CorbaException() throw() :
  ::Exception(),
  CORBA::Exception()
{
}


CorbaException::CorbaException(const CORBA::Exception &e) throw() :
  ::Exception()
{
  set(e);
}


CorbaException &CorbaException::operator=(const CORBA::Exception &e) throw()
{
  set(e);
}


void CorbaException::set(const CORBA::Exception &e) throw()
{
  (CORBA::Exception)(*this) = e;

  try { throw *this; } //FIXME_raise(); }
  catch(CORBA::NO_MEMORY e2) { error_string = _("out of memory"); }
  catch(CORBA::IMP_LIMIT e2) { error_string = _("CORBA implementation limit violated"); }
  catch(CORBA::COMM_FAILURE e2) { error_string = _("communication error"); }
  catch(CORBA::INV_OBJREF e2) { error_string = _("CORBA object reference invalid"); }
  catch(CORBA::NO_PERMISSION e2) { error_string = _("permission denied"); }
  catch(CORBA::NO_RESOURCES e2) { error_string = _("out of system resources"); }
  catch(CORBA::OBJECT_NOT_EXIST e2) { error_string = ("CORBA object does not exist"); }
  catch(CORBA::SystemException e2)
    {
      error_string =
	insert_text(_("Unknown CORBA error: %s"), e2.NP_RepositoryId());
    }
  catch(CORBA::UserException e2)
    {
      error_string = _("Unknown CORBA user exception");
    }
  catch(CORBA::Exception e2) { error_string  = "good..."; } //FIXME
  catch(...) { error_string = _("Unknown CORBA exception"); }
}


void CorbaException::raise() throw(CORBA::Exception)
{
  _raise();
}
