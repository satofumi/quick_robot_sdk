# lidar/samples

CC = $(CXX)
CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES) `urg_c-config --cflags`
INCLUDES = -I.. -I../../math -I../../system
LDFLAGS =
LDLIBS = `urg_c-config --libs` `sdl-config --libs` -lrt


TARGET = \
	sensor_parameter \
	get_distance \
	get_distance_intensity \
	get_multiecho \
	get_multiecho_intensity \
	calculate_xy \
	sync_time_stamp \
	evaluate_timestamp \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c *.cpp)

.PHONY : all clean depend
######################################################################
REQUIRE_LIBS = ../liblidar.a ../../system/libsystem.a
$(REQUIRE_LIBS) :
	cd $(@D)/ && $(MAKE) $(@F)

$(TARGET) : Connection_information.o $(REQUIRE_LIBS)

# DO NOT DELETE

Connection_information.o: Connection_information.h
calculate_xy.o: Connection_information.h
get_distance.o: Connection_information.h
get_distance_intensity.o: Connection_information.h
get_multiecho.o: Connection_information.h
get_multiecho_intensity.o: Connection_information.h
sensor_parameter.o: Connection_information.h
sync_time_stamp.o: Connection_information.h
