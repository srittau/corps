#ifndef __GAME_HH
#define __GAME_HH

/*  Interface for game class
    Copyright (C) 1998-99 Sebastian Rittau

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

#include <corps/ch-history-wrapper.hh>
#include <corps/client-wrapper.hh>
#include <corps/game-impl.hh>

#include "system.hh"


class CorbaException;
class System_Impl;


class Game : public Game_Impl
{
public:
  Game() throw();
  virtual ~Game() throw();

  // non-CORBA methods
  void broadcast(const string &text) throw();

protected:
  virtual string _join(Client_Wrapper wrapper) throw(CorbaException);
  virtual void _leave(const string &id) throw(CorbaException);

private:
  System_Impl *system_impl;

  /*** Client Handling ***/
  typedef struct
  {
    Client_Wrapper     client;
    CH_History_Wrapper history;
    string             cookie;
    string             nick;
    int                error_count; // increased on every error
  } ClientEntry;
  typedef vector<ClientEntry> ClientList;
  ClientList client_list;
  pthread_mutex_t client_list_lock;

  // Client list must be protected against access by other threads by caller!
  bool check_nick(const string &nick) const throw();
};

#endif // __GAME_HH
