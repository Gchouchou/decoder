CC := g++
SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/genAlg

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
SOURCENAMES:= $(notdir $(SOURCES))
SOURCEDIRS := $(sort $(dir $(SOURCES)))
HEADERDIRS := $(sort $(shell find $(INCDIR) -type f -name '*.h' -printf "%h\n"))
OBJECTS := $(patsubst %.$(SRCEXT),$(BUILDDIR)/%.o,$(SOURCENAMES))
DEP := $(OBJECTS:.o=.d)
CFLAGS := -g -Wall -MMD
INC := $(addprefix -I ,$(HEADERDIRS))
vpath %.$(SRCEXT) $(SOURCEDIRS)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $@

$(BUILDDIR)/%.o: %.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

-include $(DEP)

clean:
	@clear
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean