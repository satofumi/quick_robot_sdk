# system

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags`
INCLUDES =
LDFLAGS =
LDLIBS =

SYSTEM_LIB = libsystem.a
TARGET = $(SYSTEM_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
$(SYSTEM_LIB) : \
	$(SYSTEM_LIB)(Sdl_initialize.o) \
	$(SYSTEM_LIB)(delay.o) \
	$(SYSTEM_LIB)(ticks.o) \

# DO NOT DELETE

Sdl_initialize.o: Sdl_initialize.h
delay.o: delay.h
ticks.o: ticks.h detect_os.h
