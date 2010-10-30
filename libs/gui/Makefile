# gui/

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags`
INCLUDES = -I../system
LDFLAGS =
LDLIBS =

GUI_LIB = libgui.a
TARGET = $(GUI_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
$(GUI_LIB) : \
	$(GUI_LIB)(Sdl_video_initialize.o) \

# DO NOT DELETE

Sdl_video_initialize.o: Sdl_video_initialize.h
