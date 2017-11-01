bin_PROGRAMS = corps-gamelist

bindir = $(prefix)/games
localedir = $(datadir)/locale

INCLUDES = -I$(top_builddir)
DEFS = @DEFS@ -DLOCALEDIR=\"$(localedir)\"
CXXFLAGS = @CXXFLAGS@ @CORPS_CORBA_CXXFLAGS@
LDADD = @INTLLIBS@ @CORPS_CORBA_LIBS@

corps_gamelist_SOURCES = \
	main.cc \
	arghandler.cc arghandler.hh \
	gamelist.cc gamelist.hh
