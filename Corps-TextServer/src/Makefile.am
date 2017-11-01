bin_PROGRAMS = corps-textserver

bindir = $(prefix)/games
localedir = $(datadir)/locale

INCLUDES = -I$(top_builddir)
DEFS = @DEFS@ -DLOCALEDIR=\"$(localedir)\"
CXXFLAGS = @CXXFLAGS@ @CORPS_CORBA_CXXFLAGS@
LDADD = @INTLLIBS@ @CORPS_CORBA_LIBS@

corps_textserver_SOURCES = \
	main.cc \
	arghandler.cc arghandler.hh \
	game.cc game.hh \
	system.cc system.hh
