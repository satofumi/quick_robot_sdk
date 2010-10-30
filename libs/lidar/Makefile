# lidar/

CC = $(CXX)
CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `urg_c-config --cflags`
CFLAGS = $(CXXFLAGS)
INCLUDES = -I../system

LIDAR_LIB = liblidar.a
TARGET = $(LIDAR_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
	cd samples/ && $(MAKE) clean

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c *.cpp)

.PHONY : all clean depend
######################################################################
$(LIDAR_LIB) : \
	$(LIDAR_LIB)(Urg_driver.o) \

# DO NOT DELETE

Urg_driver.o: Urg_driver.h
