#
# Compile the example
#
# vim: set tabstop=8 softtabstop=8 noexpandtab :
#

# 
# Define some variables for the makefile.
# Lower case is used to avoid overwriting environment variables.
#
# 1. Define the default c++ compiler
       cxx = g++
#
# 2. Define the flags we want to pass to the c++ compiler
  cxxflags = -g -Wall $(CXXFLAGS)
#             |
#             keep debugging symbols in the object files
#
# 3. Define the flags we want to pass to the preprocessor
  cppflags = -D__I_HAVE_THE_POWER__ $(CPPFLAGS)
#             |
#            *D*efine a preprocessor variable "__I_HAVE_THE_POWER__"
#
# 4. Define where we want to build and install the code
sourcedir = src
   prefix = build
 builddir = $(prefix)/src
   bindir = $(prefix)/bin
   libdir = $(prefix)/lib
   incdir = $(prefix)/include
     dirs = $(builddir) $(bindir) $(libdir) $(incdir)
#
# 5. Define the target and objects to make cleanup easiser
   sources = $(wildcard $(sourcedir)/*.cxx)
   objects = $(patsubst $(sourcedir)/%,$(builddir)/%,$(sources:.cxx=.o))
   target = example
   library = libFakeROOT.a

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
all: $(dirs) build install

$(builddir) :
	@echo "Making \$$(builddir)..."
	@mkdir -p $(builddir)

$(bindir) :
	@echo "Making \$$(bindir)..."
	@mkdir -p $(bindir)

$(libdir) :
	@echo "Making \$$(libdir)..."
	@mkdir -p $(libdir)

$(incdir) :
	@echo "Making \$$(incdir)..."
	@mkdir -p $(incdir)

build: $(builddir)/$(target) $(dirs)
	@echo "Making build..."

install : $(builddir)/$(target) $(builddir)/$(library) 
	@echo "Making install..."
	@rsync -a $(builddir)/$(library) $(libdir)
	@rsync -a $(builddir)/$(target) $(bindir)
	@rsync -a $(wildcard $(sourcedir)/*.h) $(incdir)

# 
# Pull in dependencies for existing objects
#
-include $(objects:.o=.d)

#
# Link the library
#
$(builddir)/$(library) : $(builddir)/FakeTH1D.o
	@echo "Makeing \$$(library)..."
	$(AR) $(ARFLAGS) $@ $^ 

#
# Link the executable
#
$(builddir)/$(target) : $(objects) $(builddir)/$(library) 
	@echo "Making \$$(target)..."
	$(cxx) $(cppflags) $(cxxflags) -L$(builddir) -lFakeROOT $^ -o $@

#
# Compile the objects
#
$(builddir)/%.o : $(sourcedir)/%.cxx
	$(cxx) -c $(cppflags) $(cxxflags) $< -o $@
	@$(cxx) $(cppflags) $(cxxflags) -MM $(sourcedir)/$*.cxx > $(builddir)/$*.d
	@cp -f $(builddir)/$*.d $(builddir)/$*.d.tmp
	@sed -e 's|.*:|$(builddir)/$*.o:|' < $(builddir)/$*.d.tmp > $(builddir)/$*.d
#                  \ /\_________________/                         |
#                   |         |                                   and _overwrite_ the dependency file
#                   |         with the actual target (include the builddir)
#                   substitute the listed target
#
	@sed -e 's|.*:||' -e 's|\\$$||' < $(builddir)/$*.d.tmp | fmt -1 | sed -e 's|^ *||' -e 's|$$|:|' >> $(builddir)/$*.d
#                \     /       \     /                           \   /            \     /      \     /   |
#                 \   /         \   /                             \ /              \   /        \   /    and _append_ the dependency file
#                  \ /           \ /                               |                \ /          \ /   
#                   |             ?                                |                 |            and append a ':' to each line
#                   |             ?                                |                 then strip leading whitespace
#                   |             ?                                split the line so there is one entry per line
#                   |             strip the trailing '\' character (why is this needed!?)
#                   strip the target from the line (everything up to and including the first ':')
	@rm -f $(builddir)/$*.d.tmp

#
# We like to clean up after ourselves, but it is our
# responsibility to tell make what needs to be done
# to put things back to a pre-compiled state.
#
clean:
	rm -rf $(dirs) 

