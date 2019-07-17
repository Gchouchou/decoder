CC := g++
SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/genAlg
VPATH := $(SRCDIR)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)' -printf "%f\n")
OBJECTS := $(patsubst %.$(SRCEXT),$(BUILDDIR)/%.o,$(SOURCES))
DEB := $(OBJECTS:.o=.d)
CFLAGS := -g -Wall -MMD
INC := -I $(INCDIR)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: %.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

-include $(DEB)

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
