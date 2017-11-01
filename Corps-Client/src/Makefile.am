bin_PROGRAMS = corps-client

bindir = $(prefix)/games
localedir = $(datadir)/locale

INCLUDES = -I$(top_builddir)
CXXFLAGS = @CXXFLAGS@ @CORPS_CORBA_CXXFLAGS@
LDADD = @INTLLIBS@ @CORPS_CORBA_LIBS@

corps_client_SOURCES = \
	main.cc \
	arghandler.cc arghandler.hh \
	client.cc client.hh \
	gamelist.cc gamelist.hh
