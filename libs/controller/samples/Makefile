# controller/samples

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags`
INCLUDES = -I..
LDFLAGS =
LDLIBS = `sdl-config --libs`

TARGET = usb_joystick_view

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)


.PHONY : all clean depend
######################################################################
REQUIRE_LIBS = ../libcontroller.a ../../gui/libgui.a ../../system/libsystem.a

$(REQUIRE_LIBS) :
	cd $(@D)/ && $(MAKE) $(@F)

usb_joystick_view  : $(REQUIRE_LIBS)

# DO NOT DELETE
