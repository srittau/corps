SUBDIRS = \
	intl \
	po \
	src \
	man

EXTRA_DIST = TODO

debiandir = $(distdir)/debian
dist-debian: dist
	if [ ! -d debian ]; then \
	    echo >&2 "ERROR: You need the Debian version to create a Debian package."; \
	    exit 1; \
	fi
	tar xzf $(distdir).tar.gz
	mkdir $(debiandir)
	cp debian/{changelog,control,copyright,docs,menu,rules,undocumented} $(debiandir)
	dpkg-source -b $(distdir) $(distdir).tar.gz
	cd $(distdir) && dpkg-buildpackage -b -rfakeroot
	-rm -rf $(distdir)

dist-hook:
	rcs2log >$(distdir)/ChangeLog || echo "WARNING: ChangeLog couldn´t be created"
	find $(distdir) -type f -printf "%s\t%p\n" | sed -e "s/\.\///" | sort +1 -b > $(distdir)/MANIFEST
