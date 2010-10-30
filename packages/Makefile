# packages

# Target
PACKAGES_DIR = urg_cpp_library

all :

clean :
	for i in $(PACKAGES_DIR) ; \
	do \
	    cd $(PWD); \
	    cd $$i && if test -f Makefile; then ($(MAKE) clean && $(RM) config.log autoscan.log && cd autom4te.cache/ && $(RM) output.* traces.* requests); fi \
	done
