corpsincludedir = $(includedir)/corps

lib_LIBRARIES = libcorpscorba.a

CXXFLAGS = @CXXFLAGS@ @OMNIORB_CXXFLAGS@

INCLUDES = -I$(top_srcdir)/libcorpstool

libcorpscorba_a_SOURCES = \
	corba.cc \
	orb.cc \
	roleplayingSK.cc \
	corbaexception.cc \
	client-wrapper.cc \
	clienthandler-wrapper.cc \
	ch-history-wrapper.cc \
	game-wrapper.cc \
	gamelist-wrapper.cc \
	system-wrapper.cc \
	character-impl.cc \
	client-impl.cc \
	clienthandler-impl.cc \
	game-impl.cc \
	gamelist-impl.cc \
	property-impl.cc \
	system-impl.cc \
	thing-impl.cc

corpsinclude_HEADERS = \
	corba.hh \
	orb.hh \
	roleplaying.hh \
	corbaexception.hh \
	client-wrapper.hh \
	clienthandler-wrapper.hh \
	ch-history-wrapper.hh \
	game-wrapper.hh \
	gamelist-wrapper.hh \
	system-wrapper.hh \
	character-impl.hh \
	client-impl.hh \
	clienthandler-impl.hh \
	game-impl.hh \
	gamelist-impl.hh \
	property-impl.hh \
	system-impl.hh \
	thing-impl.hh

EXTRA_DIST = README


CORBA_SRCLIST = roleplayingSK.cc roleplaying.hh
CORBA_FILELIST = $(foreach f,$(CORBA_SRCLIST),$(distdir)/$(f))

CLEANFILES += $(CORBA_SRCLIST)

$(CORBA_SRCLIST): $(top_srcdir)/idl/roleplaying.idl $(IDL_COMPILER)
	$(IDL_COMPILER) $<

dist-hook:
	-rm $(CORBA_FILELIST)
