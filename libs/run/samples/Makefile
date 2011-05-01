# controller/samples

LIB_DIR = ../../

CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES) `urg_cpp-config --cflags` `sdl-config --cflags`
INCLUDES = -I.. -I$(LIB_DIR)/geometry -I$(LIB_DIR)/run -I$(LIB_DIR)/lidar -I$(LIB_DIR)/system
LDFLAGS = `urg_cpp-config --libs` `sdl-config --libs`
LDLIBS =

TARGET = \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
REQUIRE_LIBS = $(LIB_DIR)/run/librun_master.a $(LIB_DIR)/lidar/liblidar.a $(LIB_DIR)/geometry/libgeometry.a $(LIB_DIR)/system/libsystem.a

$(REQUIRE_LIBS) :
	cd $(@D)/ && $(MAKE) $(@F)

$(TARGET) : $(REQUIRE_LIBS)

# DO NOT DELETE
