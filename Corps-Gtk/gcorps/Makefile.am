bin_PROGRAMS = gcorps

bindir = $(prefix)/games
localedir = $(datadir)/locale
pixmapdir = $(datadir)/corps/pixmaps

INCLUDES = -I$(top_builddir) -I$(top_srcdir)/libcorpsgtk
DEFS = @DEFS@ -DLOCALEDIR=\"$(localedir)\" -DPIXMAPDIR=\"$(pixmapdir)\"
CXXFLAGS = @CXXFLAGS@ @GTKMM_CFLAGS@ @CORPS_CORBA_CXXFLAGS@
LDADD = $(top_builddir)/libcorpsgtk/libcorpsgtk.a \
	@INTLLIBS@ @GTKMM_LIBS@ @CORPS_CORBA_LIBS@

gcorps_SOURCES = \
	main.cc \
	arghandler.cc arghandler.hh \
	client.cc client.hh \
	client-gui.cc client-gui.hh \
	client-i.cc client-i.hh \
	gamelist.cc gamelist.hh \
	gui.cc gui.hh \
	gui_gamechooser.cc gui_gamechooser.hh \
	gui_gamewindow.cc gui_gamewindow.hh \
	gui_playfield.cc gui_playfield.hh \
	utils.cc utils.hh
