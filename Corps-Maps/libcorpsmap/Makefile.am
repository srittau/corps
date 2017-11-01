corpsincludedir = $(includedir)/corps
mapsetdir = $(datadir)/corps/mapsets

lib_LIBRARIES = libcorpsmap.a

CXXFLAGS = @CXXFLAGS@ @CORPS_FILE_CXXFLAGS@ @GDK_IMLIB_CFLAGS@ @GTKMM_CFLAGS@
DEFS = -DMAPSETDIR=\"$(mapsetdir)\"
INCLUDES = -I$(top_srcdir)

libcorpsmap_a_SOURCES = \
	map.cc \
	mapfile.cc \
	mapmodifier.cc \
	mapset.cc \
	mapsetfile.cc

corpsinclude_HEADERS = \
	map.hh \
	mapfile.hh \
	mapmodifier.hh \
	mapset.hh \
	mapsetfile.hh
