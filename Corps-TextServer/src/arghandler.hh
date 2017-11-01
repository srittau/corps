#ifndef ARGHANDLER_HH
#define ARGHANDLER_HH

/*  Interface for argument handling class
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


class ArgHandler
{
public:
  ArgHandler(int argc, char *argv[]) throw();

  const string &getGLServer() const throw() { return gamelist_server; }
  const string &getGameName() const throw() { return game_name; }
  const string &getGameDescription() const throw() { return game_description; }
  const string &getSystemName() const throw() { return system_name; }
  const string &getSystemDescription() const throw() { return system_description; }
  const string &getLanguage() const throw() { return language; }

private:
  static struct option ArgArray[];
  static const char OptString[];

  string gamelist_server;
  string game_name;
  string game_description;
  string system_name;
  string system_description;
  string language;
};

#endif // ARGHANDLER_HH
