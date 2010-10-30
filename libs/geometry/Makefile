# geometry/

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags`
INCLUDES = -I../math -I../system
LDFLAGS =
LDLIBS =

GEOMETRY_LIB = libgeometry.a
TARGET = $(GEOMETRY_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
$(GEOMETRY_LIB) : \
	$(GEOMETRY_LIB)(Angle.o) \

# DO NOT DELETE

Position.o: Angle.h
Angle.o: Angle.h
