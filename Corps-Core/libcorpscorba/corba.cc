/*  CORBA support functions
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

#include <i18n.hh>

#include <libintl.h>

#include <omniORB2/CORBA.h>

#include "corba.hh"
#include "exception.hh"
#include "tools.hh"


::Exception convert_CORBA_Exception(CORBA::Exception &e) throw()
{
  //FIXME: handle some standard exceptions

  string error;

  CORBA::SystemException *se = CORBA::SystemException::_narrow(&e);
  CORBA::UserException *ue = CORBA::UserException::_narrow(&e);
  if(se)
    error = insert_text(_("CORBA error: %s"), se->NP_RepositoryId());
  else if(ue)
    error = _("unknown CORBA error");
  else
    error = _("invalid CORBA error");

  return ::Exception(error);
}
