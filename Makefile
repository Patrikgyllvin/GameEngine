RTDIR = .
SRCDIR = $(RTDIR)/Source/src
INCDIR = $(RTDIR)/Source/include
BINDIR = $(RTDIR)/bin
OBJDIR = $(RTDIR)/obj

CC = g++
#DEBUG FLAGS
CFLAGS = --std=c++11 -Wall -O0 -g -c -DDebug
#RELEASE FLAGS
#CFLAGS = --std=c++11 -Wall -O2 -c
LFLAGS = -lGL -lGLEW -lglfw
INCLUDE = -I$(INCDIR)

EXEC = Game

_SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*.cpp) \
	$(wildcard $(SRCDIR)/*/*/*/*.cpp) $(wildcard $(SRCDIR)/*/*/*/*/*.cpp)

SOURCES = $(subst $(SRCDIR)/,,$(_SOURCES))

_OBJS = $(basename $(SOURCES))
_OBJECTS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
OBJS = $(addsuffix .o,$(_OBJECTS))

.PHONY: all

all: $(OBJS)

.PHONY: rebuild

rebuild: clean all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(EXEC): $(BINDIR) $(OBJS)
	$(CC) -o $(BINDIR)/$(EXEC) $(OBJS) $(LFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUT): 

.PHONY: clean

clean:
	rm -rf $(BINDIR) $(OBJDIR)