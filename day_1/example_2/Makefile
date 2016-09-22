#
# Compile the example
#
# vim: set tabstop=8 softtabstop=8 noexpandtab :
#

#
# The .PHONY target tells make that the following targets
# do not actually create any objects themselves, and should
# not do any checks on timestamps to determine if they need
# to be processed.
#
.PHONY: all clean

#
# The default target is 'all'
# This says that all depends on 'example'.
#
all: example

example: example.cxx hello.o
	g++ example.cxx hello.o -o example

hello.o: hello.cxx hello.h
	g++ -c -Wnone hello.cxx -o hello.o

#
# We like to clean up after ourselves, but it is our
# responsibility to tell make what needs to be done
# to put things back to a pre-compiled state.
#
clean:
	rm -f example hello.o

