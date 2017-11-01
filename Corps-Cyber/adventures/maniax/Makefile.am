maniaxdir = $(libdir)/corps/adventures/maniax
localedir = $(datadir)/locale

maniax_PROGRAMS = maniax

INCLUDES = \
	-I$(top_builddir) \
	-I$(top_builddir)/system
DEFS = @DEFS@ -DLOCALEDIR=\"$(localedir)\"
CXXFLAGS = @CXXFLAGS@ @CORPS_CORBA_CXXFLAGS@
LDADD = $(top_builddir)/system/libcyber.a \
	@INTLLIBS@ @CORPS_CORBA_LIBS@

maniax_SOURCES = \
	maniax.cc \
	arghandler.cc arghandler.hh \
	game.cc game.hh \
	plot.cc plot.hh

maniax_DATA = supermarket.xml
EXTRA_DIST = $(maniax_DATA)
