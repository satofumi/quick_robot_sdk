# run_wired_controller

LIBS_DIR = ../../libs

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `sdl-config --cflags` `urg_c-config --cflags`
INCLUDES = -I$(LIBS_DIR)/controller -I$(LIBS_DIR)/run -I$(LIBS_DIR)/geometry
LDFLAGS =
LDLIBS = `sdl-config --libs` `urg_c-config --libs`

TARGET = run_wired_controller

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

run_wired_controller  : $(REQUIRE_LIBS)

# DO NOT DELETE
