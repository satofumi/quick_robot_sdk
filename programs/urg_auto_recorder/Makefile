# programs/urg_auto_recorder

LIBS_DIR = ../../libs

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `urg_c-config --cflags`
INCLUDES =
LDFLAGS =
LDLIBS = `urg_c-config --libs`

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

urg_auto_recorder  : $(REQUIRE_LIBS)
# DO NOT DELETE
