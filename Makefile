# Makefile for the ctopy project

VERS=$(shell sed <ctopy.spec -n -e '/Version: \(.*\)/s//\1/p')

MANDIR=$(DESTDIR)/usr/share/man/man1
BINDIR=$(DESTDIR)/usr/bin

DOCS    = README COPYING ctopy.xml ctopy.1
SOURCES = ctopy Makefile $(DOCS) ctopy.spec

all: ctopy-$(VERS).tar.gz

install: ctopy.1
	cp ctopy buildrpms $(BINDIR)
	gzip <ctopy.1 >$(MANDIR)/ctopy.1.gz

ctopy.1: ctopy.xml
	xmlto man ctopy.xml
ctopy.html: ctopy.xml
	xmlto html-nochunks ctopy.xml

ctopy-$(VERS).tar.gz: $(SOURCES)
	@mkdir ctopy-$(VERS)
	@cp $(SOURCES) ctopy-$(VERS)
	@tar -czf ctopy-$(VERS).tar.gz ctopy-$(VERS)
	@rm -fr ctopy-$(VERS)

pychecker:
	ln -f ctopy ctopy.py
	pychecker --only --limit 50 ctopy.py
	rm -f ctopy.py

makeregress:
	ctopy <testload.c >testload.py

regress:
	@ctopy <testload.c >testload.py-trial
	@if diff -u testload.py testload.py-trial; \
	then echo "Test succeeded"; \
	else echo "Test failed"; fi
	@rm -f testload.py-trial

clean:
	rm -f *.html *.1 *.pyc testload.py-trial SHIPPER.* typescript *.tar.gz

dist: ctopy-$(VERS).tar.gz

release: ctopy-$(VERS).tar.gz ctopy.html
	shipper -u -m -t; make clean


