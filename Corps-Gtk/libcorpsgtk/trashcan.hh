#ifndef TRASHCAN_HH
#define TRASHCAN_HH

/*  Garbage collection
    Copyright (C) 1999 Sebastian Rittau
    Version: 1.0.2 1999-01-18

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

#include <vector>


class Trashcan : private vector<void *> {
public:
  ~Trashcan() throw();

  void add(void *p) throw();
  // call this method from a save point to clean up
  void empty() throw();
};

#endif // TRASHCAN_HH
