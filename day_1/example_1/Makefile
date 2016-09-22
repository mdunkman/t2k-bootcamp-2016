#
# Compile the example
# vim: set tabstop=8 softtabstop=8 noexpandtab :
#

# 
# Everything before the ':' defines a _target_
# and its _dependencies_ are listed on the same line.
#
# After the first line we have one or more lines indented
# with a <TAB> which define the _rules_. These rules are
# the commands we send the shell to build the target.
#
example: example.cxx
	@echo "Compiling example.cxx into ./example"
#	|
#      '@' means do not print the command before executing it.
#       This is super useful for commands like `echo` and internal commands we want to hide.
#
	g++ example.cxx -o example

clean:
	rm example

.PHONY: clean

