noinst_PROGRAMS = corps-testmap

CXXFLAGS = @CXXFLAGS@ @CORPS_FILE_CXXFLAGS@ @GDK_IMLIB_CFLAGS@ @GTKMM_CFLAGS@
INCLUDES = -I$(top_srcdir)/libcorpsmap
LDADD = $(top_builddir)/libcorpsmap/libcorpsmap.a \
	@CORPS_FILE_LIBS@ @GDK_IMLIB_LIBS@

corps_testmap_SOURCES = \
	corps-testmap.cc

EXTRA_DIST = map.xml
