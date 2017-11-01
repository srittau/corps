/*  Client class for GCorps
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

#include <corps/exception.hh>
#include <corps/game-wrapper.hh>
#include <corps/orb.hh>

#include "client.hh"
#include "client-i.hh"
#include "gui.hh"
#include "trashcan.hh"


extern CORPS_ORB *orb;
extern GUI       *gui;
extern Trashcan trash;


Client::client_list_type Client::client_list;


Client::Client() throw(Exception) :
  cl_impl(0),
  c_gui(*this),

  game(0)
{
  cl_impl = new Client_I(*this);
  cl_impl->_obj_is_ready(orb->getBOA());

  //FIXME: protect with semaphores
  client_list.insert(client_list.end(), this);
  listed = true;
  c_gui.show();
}


Client::~Client() throw()
{
  delete_from_client_list();

  try { if(game) { game->leave(); } } catch(...) {}
  cl_impl->_dispose();

  if(game)
    delete game;
}


void Client::delete_client() throw()
{
  delete_from_client_list();
  if(client_list.empty())
    gui->quit();

  try { if(game) { game->leave(); } } catch(...) {}
  cl_impl->_dispose();

  trash.add(this);
}


void Client::delete_all() throw()
{
  if(client_list.empty())
    return;

  client_list_type::size_type pos = 0;
  while(pos < client_list.size())
    {
      client_list[pos]->listed = false;
      delete client_list[pos]; // this works because method is static
      pos++;
    }

  client_list.clear();
}


void Client::delete_from_client_list() throw()
{
  if(!listed || client_list.empty())
    return;

  client_list_type::size_type pos = 0;
  while(pos < client_list.size())
    {
      if(client_list[pos] == this)
	{
	  client_list.erase(client_list.begin() + pos);
	  listed = false;
	  return;
	}
      pos++;
    }

  // We should never get here
}


void Client::connect_to_game(const Game_Wrapper &g) throw(CorbaException)
{
  game = new Game_Wrapper(g);
  game->join(cl_impl);
}


void Client::kick(const string &reason) throw()
{
  c_gui.kick(reason);
  delete game; game = 0;
}


void Client::print_to_game(const string &text) throw(Exception)
{
  if(!game)
    throw Exception(Exception::INTERNAL_ERROR);

  //FIXME:  game->print(text.c_str());
}
