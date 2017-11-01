bindir = $(prefix)/games

bin_PROGRAMS = corps-maptool

CXXFLAGS = @CFLAGS@ @CORPS_FILE_CXXFLAGS@ @THREAD_CFLAGS@ \
	@GDK_IMLIB_CFLAGS@ @GTKMM_CFLAGS@
INCLUDES = -I$(top_builddir) -I$(top_srcdir)/libcorpsgtk
DEFS = @DEFS@ -DLOCALEDIR=\"$(localedir)\"
LDADD = @INTLLIBS@ @GDK_IMLIB_LIBS@ @GTKMM_LIBS@ @THREAD_LIBS@ \
	@CORPS_FILE_LIBS@ \
	-lcorpsmap \
	$(top_builddir)/libcorpsgtk/libcorpsgtk.a

corps_maptool_SOURCES = \
	main.cc \
	arghandler.cc \
	gui.cc \
	gui_iconview.cc \
	gui_mapwidget.cc \
	gui_mapwindow.cc \
	gui_sizereq.cc

noinst_HEADERS = \
	arghandler.hh \
	gui.hh \
	gui_iconview.hh \
	gui_mapwidget.hh \
	gui_mapwindow.hh \
	gui_sizereq.hh
