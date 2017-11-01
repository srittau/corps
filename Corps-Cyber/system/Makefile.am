cyberdir = $(libdir)/corps/systems/cyber
dtddir = $(libdir)/sgml/dtd
cssdir = $(libdir)/sgml/stylesheet/css

cyber_LIBRARIES = libcyber.a

CXXFLAGS = @CXXFLAGS@ @CORPS_FILE_CXXFLAGS@ @CORPS_CORBA_CXXFLAGS@
INCLUDES = -I$(top_srcdir)

libcyber_a_SOURCES = \
	character.cc \
	system.cc

noinst_HEADERS = \
	character.hh \
	system.hh

dtd_DATA = cyber_character.dtd
css_DATA = cyber_character.css

EXTRA_DIST = $(dtd_DATA) $(css_DATA)
