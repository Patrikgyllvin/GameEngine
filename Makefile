RTDIR = .
SRCDIR = $(RTDIR)/Source/src
INCDIR = $(RTDIR)/Source/include
LIBDIR = $(RTDIR)/Include
BINDIR = $(RTDIR)/bin
OBJDIR = $(RTDIR)/obj

CC = g++
#DEBUG FLAGS
CFLAGS = --std=c++11 -Wall -O2 -g -c -DDebug -D_MAC_MAKEFILE
#RELEASE FLAGS
#CFLAGS = --std=c++11 -Wall -O2 -c -D_MAC_MAKEFILE
LFLAGS = -lGL -lGLEW -lglfw
INCLUDE = -I$(INCDIR)

ifeq ($(OS),Windows_NT)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LFLAGS = -L/usr/local/lib -lpng -lGLEW -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
        INCLUDE += -I/usr/local/include -I./Include
	endif
endif

EXEC = Game

_SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*.cpp) \
	$(wildcard $(SRCDIR)/*/*/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*/*/*.cpp)

SOURCES = $(subst $(SRCDIR)/,,$(_SOURCES))

_HEADERS = $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/*/*.h) $(wildcard $(INCDIR)/*/*/*.h) \
	$(wildcard $(INCDIR)/*/*/*/*.h) $(wildcard $(INCDIR)/*/*/*/*/*.h)

HEADERS = $(subst $(INCDIR)/,,$(_HEADERS))

_OBJS = $(basename $(SOURCES))
_OBJECTS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
OBJS = $(addsuffix .o,$(_OBJECTS))

_LIBSOURCES = $(wildcard $(LIBDIR)/*.cpp) $(wildcard $(LIBDIR)/*/*.cpp) $(wildcard $(LIBDIR)/*/*/*.cpp) \
	$(wildcard $(LIBDIR)/*/*/*/*.cpp) $(wildcard $(LIBDIR)/*/*/*/*/*.cpp)

LIBSOURCES = $(subst $(LIBDIR)/,,$(_LIBSOURCES))

_LIBOBJS = $(basename $(LIBSOURCES))
_LIBOBJECTS = $(patsubst %,$(OBJDIR)/%,$(_LIBOBJS))
LIBOBJS = $(addsuffix .o,$(_LIBOBJECTS))

.PHONY: all

all: $(LIBOBJS) $(OBJS) $(EXEC)

.PHONY: rebuild

rebuild: clean all

.PHONY: run

run: $(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(OBJDIR)/%.o: $(LIBDIR)/%.cpp | $(OBJDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(EXEC): $(BINDIR) $(OBJS) $(LIBOBJS)
	$(CC) -o $</$@ $(OBJS) $(LIBOBJS) $(LFLAGS)
	$(BINDIR)/$(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)
	cp -r $(RTDIR)/Res $(BINDIR)/Res

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUT):

.PHONY: clean

clean:
	rm -rf $(BINDIR) $(OBJDIR)
