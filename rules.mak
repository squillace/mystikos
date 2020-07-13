ifndef SUBDIR
$(error "please define SUBDIR variable")
endif

OBJECTS = $(SOURCES:.c=.o)
__OBJECTS = $(addprefix $(SUBOBJDIR)/,$(OBJECTS))

define NL


endef

ifdef PROGRAM
__PROGRAM = $(SUBBINDIR)/$(PROGRAM)
$(__PROGRAM): dirs $(__OBJECTS)
	mkdir -p $(SUBBINDIR)
	gcc -o $(__PROGRAM) $(CFLAGS) $(__OBJECTS) $(LDFLAGS)
endif

ifdef ARCHIVE
__ARCHIVE = $(SUBLIBDIR)/$(ARCHIVE)
$(__ARCHIVE): dirs $(__OBJECTS)
$(__ARCHIVE): $(__OBJECTS)
	mkdir -p $(SUBLIBDIR)
	ar rv $(__ARCHIVE) $(__OBJECTS)
endif

$(SUBOBJDIR)/%.o: %.c
	mkdir -p $(SUBOBJDIR)
	$(shell mkdir -p $(shell dirname $@))
	$(CC) -c $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ $<

dirs:
ifdef DIRS
	$(foreach i, $(DIRS), $(MAKE) -C $(i) $(NL) )
endif

clean:
	rm -f $(__OBJECTS) $(__PROGRAM) $(__ARCHIVE) $(CLEAN)
ifdef DIRS
	$(foreach i, $(DIRS), $(MAKE) -C $(i) clean $(NL) )
endif