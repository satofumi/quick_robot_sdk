# controller

CC = $(CXX)
CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags`
INCLUDES = -I../gui

CONTROLLER_LIB = libcontroller.a
TARGET = $(CONTROLLER_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
	cd samples/ && $(MAKE) clean

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
$(CONTROLLER_LIB) : \
	$(CONTROLLER_LIB)(Usb_joystick.o) \

# DO NOT DELETE

Usb_joystick.o: Joystick.h
Usb_joystick.o: Usb_joystick.h Joystick.h
