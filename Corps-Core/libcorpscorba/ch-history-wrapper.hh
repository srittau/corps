#ifndef CH_HISTORY_WRAPPER_HH
#define CH_HISTORY_WRAPPER_HH

/*  Interface for CH-History-Wrapper
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

#include "clienthandler-wrapper.hh"
#include "roleplaying.hh"

class CorbaException;


class CH_History_Wrapper : public ClientHandler_Wrapper
{
public:
  CH_History_Wrapper(const ClientHandler_Wrapper &o) throw(CorbaException);

  operator RolePlaying::CH_History_var &() throw()
    { return ch_history; }
  operator const RolePlaying::CH_History_var &() const throw()
    { return ch_history; }

  // CORBA methods
  void append_text(const string &text) throw(CorbaException);
  void clear() throw(CorbaException);

private:
  RolePlaying::CH_History_var ch_history;
};

#endif // CLIENTHANDLER_WRAPPER_HH
