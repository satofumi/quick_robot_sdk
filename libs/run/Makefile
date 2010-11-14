# run/

CXXFLAGS = -g -O0 -Wall -Werror -W $(INCLUDES) `urg_c-config --cflags`
CFLAGS = $(CXXFLAGS)
INCLUDES = -I../geometry -I../math -I../system -I../run_target

RUN_LIB = librun.a
TARGET = $(RUN_LIB)

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
	cd samples/ && $(MAKE) clean

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c *.cpp)

.PHONY : all clean depend
######################################################################
$(RUN_LIB) : \
	$(RUN_LIB)(c_run_driver.o) \
	$(RUN_LIB)(htoi.o) \
	$(RUN_LIB)(Run_driver.o) \

htoi.o : ../run_target/htoi.c
	$(CC) $(CFLAGS) $< -c -o $@

# DO NOT DELETE

c_run_driver.o: run_driver_t.h
c_run_driver.o: c_run_driver.h run_driver_t.h
Run_driver.o: Run_driver.h c_run_driver.h run_driver_t.h
