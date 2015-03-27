COMPILER = g++
CFLAGS   = -Wextra -g -MMD -MP
LDFLAGS  = -static -lsfml-graphics -lsfml-window -lsfml-system -std=c++0x -static-libstdc++ -static-libgcc
LIBS     =
INCLUDE  = -I../include
TARGET   = ../bin/$(shell basename `readlink -f ..`)
OBJDIR   = ./obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR = .
endif
SOURCES  = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
DEPENDS  = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)
	@rmdir --ignore-fail-on-non-empty `readlink -f $(OBJDIR)`

-include $(DEPENDS)