#!/bin/sh
# Run this to generate all the initial makefiles, etc.
#
# Partly stolen from GTK+

PACKAGE="corps-cyber"

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

ORIGDIR=`pwd`
cd $srcdir

echo "Creating ChangeLog..."
touch ChangeLog
echo "Running gettextize -f..."
echo "no" | gettextize -f
echo "Running aclocal..."
aclocal
echo "Running autoconf..."
autoconf
echo "Running autoheader..."
autoheader
echo "Running automake -a --gnu..."
automake -a --gnu
echo "Generating po/POTFILES.in..."
find . -name "*.c" -or -name "*.cc" | xargs grep -l gettext > po/POTFILES.in

cd $ORIGDIR

$srcdir/configure "$@"

echo
echo "Now type 'make' to compile $PACKAGE."
