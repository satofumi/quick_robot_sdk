## Makefile.am -- Process this file with automake to produce Makefile.in

SUBDIRS = src sample
bin_SCRIPTS = urg_cpp-config

$(PACKAGE)-$(VERSION).tar.gz: dist

zip: $(PACKAGE)-$(VERSION).tar.gz
	$(RM) -rf $(PACKAGE)-$(VERSION)
	tar zxf $(PACKAGE)-$(VERSION).tar.gz
	find $(PACKAGE)-$(VERSION) -name '*.[ch]*' | xargs nkf -s --overwrite
	zip -r $(PACKAGE)-$(VERSION).zip $(PACKAGE)-$(VERSION)/
	$(RM) -rf $(PACKAGE)-$(VERSION)
	$(RM) $(PACKAGE)-$(VERSION).tar.gz
