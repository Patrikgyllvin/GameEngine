RTDIR = .
SRCDIR = $(RTDIR)/Source/src
INCDIR = $(RTDIR)/Source/include
BINDIR = $(RTDIR)/bin
OBJDIR = $(RTDIR)/obj

CC = g++
CFLAGS = --std=c++11 -Wall -O2 -c
LFLAGS = -lGL -lGLEW -lGLFW
INCLUDE = -I$(INCDIR)
INCLUDE_RT = -I../$(INCDIR)

SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*.cpp) \
	$(wildcard $(SRCDIR)/*/*/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*/*/*.cpp)

SOURCES_RT = $(patsubst %,../%,$(SOURCES))

build: $(SOURCES) createdirs
	cd $(OBJDIR); \
	$(CC) $(CFLAGS) $(INCLUDE_RT) $(SOURCES_RT)

createdirs:
	mkdir -p $(BINDIR) $(OBJDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)