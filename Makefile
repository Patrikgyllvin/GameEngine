RTDIR = .
SRCDIR = $(RTDIR)/src
INCDIR = $(RTDIR)/include
BINDIR = $(RTDIR)/bin
OBJDIR = $(RTDIR)/obj

CXX = g++
CXXFLAGS = --std=c++17 -Wall -Werror

LDFLAGS = -lGL -lGLEW -lglfw -lpng
INCLUDE = -I$(INCDIR)

ifeq ($(OS),Windows_NT)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -L/usr/local/lib -lpng -lGLEW -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
        INCLUDE += -I/usr/local/include -I./Include
	endif
endif

EXEC = Game

SRCS := $(shell find $(SRCDIR) -name "*.cpp")
INCLUDES := $(shell find $(INCDIR) -name "*.h") $(shell find $(SRCDIR) -name "*.h") $(shell find $(INCDIR) -name "*.hpp")
OBJS := $(SRCS:$(SRCDIR)/%.cpp=%.o)

#DEBUG
DBGDIR = debug
DBGBINDIR = $(BINDIR)/$(DBGDIR)
DBGOBJDIR = $(OBJDIR)/$(DBGDIR)
DBGEXEC = $(DBGBINDIR)/$(EXEC)
DBGOBJS = $(addprefix $(DBGOBJDIR)/, $(OBJS))
DBGDEPS = $(DBGOBJS:%.o=%.d)
DBGCXXFLAGS = -O0 -g -fsanitize=address -DDEBUG
DBGLDFLAGS = -fsanitize=address

#RELEASE
RELDIR = release
RELBINDIR = $(BINDIR)/$(RELDIR)
RELOBJDIR = $(OBJDIR)/$(RELDIR)
RELEXEC = $(RELBINDIR)/$(EXEC)
RELOBJS = $(addprefix $(RELOBJDIR)/, $(OBJS))
RELDEPS = $(RELOBJS:%.o=%.d)
DBGCXXFLAGS = -O0 -g -fsanitize=address -DDEBUG
RELCXXFLAGS = -O2 -DNDEBUG
RELLDFLAGS =

.PHONY: all debug run_debug release run_release rebuild clean

# Default
all: release

rebuild: clean all

clean:
	rm -rf $(BINDIR) $(OBJDIR)

# Debug
debug: $(DBGEXEC) run_debug

run_debug:
	$(DBGEXEC)

-include $(DBGDEPS)

$(DBGOBJS): $(DBGOBJDIR)/%.o: $(SRCDIR)/%.cpp | $(DBGOBJDIR)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) $(INCLUDE) -MMD -c $< -o $@

$(DBGEXEC): $(DBGOBJS) | $(DBGBINDIR)
	$(CXX) $(LDFLAGS) $(DBGLDFLAGS) $^ -o $@

$(DBGOBJDIR):
	mkdir -p $@

$(DBGBINDIR):
	mkdir -p $@
	cp -r $(RTDIR)/Res $(DBGBINDIR)/Res

# Release
release: $(RELEXEC) run_release

run_release:
	$(RELEXEC)

-include $(RELDEPS)

$(RELOBJS): $(RELOBJDIR)/%.o: $(SRCDIR)/%.cpp | $(RELOBJDIR)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) $(INCLUDE) -MMD -c $< -o $@

$(RELEXEC): $(RELOBJS) | $(RELBINDIR)
	$(CXX) $(LDFLAGS) $(RELLDFLAGS) $^ -o $@

$(RELOBJDIR):
	mkdir -p $@

$(RELBINDIR):
	mkdir -p $@
	cp -r $(RTDIR)/Res $(RELBINDIR)/Res