# programs/urg_auto_recorder

LIBS_DIR = ../../libs

CC = g++
CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `urg_cpp-config --cflags`
INCLUDES =
LDFLAGS =
LDLIBS = `urg_cpp-config --libs`

TARGET = urg_auto_recorder

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.cpp)

.PHONY : all clean depend
######################################################################
REQUIRE_LIBS =

$(REQUIRE_LIBS) :
	cd $(@D)/ && $(MAKE) $(@F)

urg_auto_recorder : record_utilities.o urg_record_utilities.o $(REQUIRE_LIBS)

# DO NOT DELETE

record_utilities.o: record_utilities.h
urg_auto_recorder.o: record_utilities.h urg_record_utilities.h
urg_record_utilities.o: urg_record_utilities.h
