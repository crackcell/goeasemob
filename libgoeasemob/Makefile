# Author:  Menglong TAN <tanmenglong@gmail.com>
# Date:    Sun Aug 21 14:08:24 2016
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include Makefile.env

.PHONY : all clean help

all : output

output :
	mkdir -p output/lib output/include
	$(MAKE) -C src
	cp -r include/* output/include/
	cp -r lib/* output/lib/
	cp src/*.a output/lib/

clean :
	rm -rf output
	$(MAKE) clean -C src

help :
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  clean     clean objects and the executable file.'
	@echo '  help      print this message.'
	@echo
