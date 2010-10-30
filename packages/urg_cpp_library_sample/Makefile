# urg_cpp_library_sample

CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES) `urg_cpp-config --cflags`
LDFLAGS =
LDLIBS = `urg_cpp-config --libs`

TARGET = \
	get_distance \
	get_distance_intensity \
	get_multiecho \
	get_multiecho_intensity \
	calculate_xy \
	sensor_parameter \
	sync_time_stamp \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

get_distance : Connection_information.o
get_distance_intensity : Connection_information.o
get_multiecho : Connection_information.o
get_multiecho_intensity : Connection_information.o
calculate_xy : Connection_information.o
sensor_parameter : Connection_information.o
sync_time_stamp : Connection_information.o
