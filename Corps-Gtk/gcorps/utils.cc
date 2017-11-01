/*  Miscellaneous utility functions
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

#include "utils.hh"


template<class C>
void sort_list_by_string(C **list, const string &(C::*method)()) throw()
{
    if(!list)
	return;

    C **start;
    C **current;

    start = list;
    while(*start) {
	current = start;
	current--;
	while(current >= list && strcasecmp((*start)->method->c_str(), (*current)->method->c_str()) < 0)
	    current--;
	current++;
	if(current < start) {
	    C *tmp = *current;
	    while(current < start) {
		current = current[1];
		current++;
	    }
	    *start = tmp;
	}
	start++;
    }
}
