RTDIR = .
SRCDIR = $(RTDIR)/Source/src
INCDIR = $(RTDIR)/Source/include
BINDIR = $(RTDIR)/bin
OBJDIR = $(RTDIR)/obj

CC = g++
CFLAGS = --std=c++11 -Wall -O2 -c
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

all: obj $(OBJS)

.PHONY: rebuild

rebuild: clean all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(EXEC): bin $(OBJS)
	$(CC) -o $(BINDIR)/$(EXEC) $(OBJS) $(LFLAGS)

bin:
	mkdir -p $(BINDIR)

obj:
	mkdir -p $(OBJDIR)

$(OUT): 

.PHONY: clean

clean:
	rm -rf $(BINDIR) $(OBJDIR)