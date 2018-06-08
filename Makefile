CXX = g++
CPPFLAGS = -MMD -MP -Wall -std=c++11
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_ttf

SRCDIR = src
BUILDDIR = build
TARGET = bin/8Chips

SRCS = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJS = $(SRCS:src/%.cpp=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRCDIR) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(DEPS) $(TARGET)

-include $(DEPS)