# run_urg_wired_recorder

LIBS_DIR = ../../libs

CC = g++
CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags` `urg_cpp-config --cflags`
INCLUDES = -I../run_wired_controller -I../urg_auto_recorder -I$(LIBS_DIR)/controller -I$(LIBS_DIR)/run -I$(LIBS_DIR)/geometry
LDFLAGS =
LDLIBS = `sdl-config --libs` `urg_cpp-config --libs`

TARGET = run_urg_wired_recorder

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
REQUIRE_LIBS = $(LIBS_DIR)/run/librun.a $(LIBS_DIR)/controller/libcontroller.a $(LIBS_DIR)/gui/libgui.a $(LIBS_DIR)/geometry/libgeometry.a $(LIBS_DIR)/system/libsystem.a

$(REQUIRE_LIBS) :
	cd $(@D)/ && $(MAKE) $(@F)

run_urg_wired_recorder : ../run_wired_controller/run_joystick_control.o ../urg_auto_recorder/record_utilities.o ../urg_auto_recorder/urg_record_utilities.o $(REQUIRE_LIBS)
# DO NOT DELETE
