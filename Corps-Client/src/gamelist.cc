/*  Handling of game lists
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
#include <vector>

#include <libintl.h>

#include <corps/corbaexception.hh>
#include <corps/game-wrapper.hh>
#include <corps/gamelist-wrapper.hh>
#include <corps/orb.hh>
#include <corps/roleplaying.hh>
#include <corps/tools.hh>

#include "gamelist.hh"

class Exception;

extern CORPS_ORB *orb;


GameList_Handler::GameList_Handler(const string &id)
  throw(CorbaException,Exception) :
  gamelist()
{
  CORBA::Object_var o = orb->string_to_object(id);
  RolePlaying::GameList_var ptr = RolePlaying::GameList::_narrow(o);
  if(CORBA::is_nil(ptr))
    throw Exception(gettext("specified object reference is not a game list"));
  gamelist = GameList_Wrapper(ptr);
}


Game_Wrapper GameList_Handler::get_game() throw(CorbaException,Exception)
{
  GameList glist;
  unsigned long int num = 0; // number chosen

  // first, build list of available games
  GameList list = gamelist.get_list();
  vector<string> name_list;
  vector<string> system_list;

  unsigned int gamepos = 0;
  for(unsigned int pos = 0; pos < list.size(); pos++)
    {
      try
	{
	  glist.insert(glist.end(), list[pos]);
	  name_list.insert(name_list.end(), list[pos].get_name());
	  system_list.insert(system_list.end(),
			     list[pos].get_system().get_name());
	}
      catch(...) {} // we skip any game that has problems
    }

  if(glist.empty())
    {
      cout << gettext("Sorry, the list of games is empty.") << endl;
      exit(0);
    }

  cout << gettext("Please choose a game from the following list:")
       << endl << endl;
  for(unsigned int pos = 0; pos < glist.size(); pos++)
    cout << "[" << pos+1 << "] " << name_list[pos] << " ("
	 << system_list[pos] << ")" << endl;
  cout << gettext("Press Return to cancel.") << endl << endl; //FIXME: actually implement

  // now ask for a game
  bool valid = false;
  do
    {
      string input;
      cin >> input;
      char *endptr;
      num = strtoul(input.c_str(), &endptr, 10);
      if(input.empty() || *endptr || num < 1 || num > glist.size())
	cout << gettext("Invalid input!") << endl;
      else
	valid = true;
    } while(!valid);

  cin.ignore();

  return glist[num-1];
}
