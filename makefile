#!/usr/bin/make -f
include Constants.mk
# $@ name des object files = name auf der linken Seite vom Doppelpunkt des Targets
# $< erste abhaengigkeit, $< das erste Element in der Liste der Abhaengigkeiten
# $@ --> linke Seite vom Doppelpunkt
# $^ --> rechte Seite vom Doppelpunkt

SUBDIRS = $(AUTOMATDIR) $(BUFFERDIR) $(COMMONDIR) $(SYMBOLTABLEDIR) $(SCANNERDIR) $(PARSERDIR)
SUBDIRSCLEAN = $(addprefix clean,$(SUBDIRS))
.PHONY: all clean $(SUBDIRS) $(SUBDIRSCLEAN)

all: $(SUBDIRS)
$(SUBDIRS): Common
	$(shell mkdir -p $(@)/$(OBJDIR))
	$(shell mkdir -p $(@)/$(BINDIRTEST))
	$(MAKE) -C $(@) $(if $(findstring Parser,$@), makeTestParser, $(@)OBJTarget)

Scanner: Automat Buffer Symboltable
Parser: Scanner

clean: $(SUBDIRSCLEAN)
$(SUBDIRSCLEAN): clean%:
	$(MAKE) -C $* $(@)
