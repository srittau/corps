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

/*
    This class is responsible for handling all non-GUI related argument
    handling.
*/

#include <string>
#include <vector>

#include <getopt.h>


class Exception;


class ArgHandler
{
public:
  typedef vector<string> ArgList;

  ArgHandler(int argc, char *argv[]) throw(Exception);

  const ArgList &get_extra_args() throw() { return extra_args; }

private:
  static struct option arguments[];

  ArgList extra_args;
};

#endif /* ARGHANDLER_HH */
