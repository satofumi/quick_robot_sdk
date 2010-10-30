# run_drive/test

CC = $(CXX)
CXXFLAGS = -g -O0 -Wall -Werror $(INCLUDES)
INCLUDES = -I..

TARGET = wheel_velocity_test

all : $(TARGET) test

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.cpp)

test : all_test
	./all_test

######################################################################
TEST_OBJS = all_test.o Connection_utilities_test.o connection_dummy.o connection_utilities.o std_string.o Run_commands_test.o protocol_handler.o run_commands.o htoi.o

all_test : $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $@ `cppunit-config --libs` $(TEST_LDLIBS)

all_test.o : ../../unittest/all_test.cpp
	$(CXX) $(CXXFLAGS) `cppunit-config --cflags` $< -c -o $@

connection_utilities.o : ../connection_utilities.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

protocol_handler.o : ../protocol_handler.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

run_commands.o : ../run_commands.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

std_string.o : ../std_string.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

htoi.o : ../htoi.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

# DO NOT DELETE

Connection_utilities_test.o: Connection_utilities_test.h
Connection_utilities_test.o: ../connection_utilities.h host_connection.h
Connection_utilities_test.o: ../connection.h
Run_commands_test.o: Run_commands_test.h host_connection.h
Run_commands_test.o: ../connection_utilities.h ../connection.h
Run_commands_test.o: ../protocol_handler.h ../run_t.h ../controller_config.h
Run_commands_test.o: ../run_system_t.h ../odometry_t.h ../path_t.h
Run_commands_test.o: ../wheel_t.h ../encoder_t.h ../motor_t.h
connection_dummy.o: ../connection.h
wheel_velocity_test.o: ../wheel_velocity.c ../wheel_velocity.h ../wheel_t.h
wheel_velocity_test.o: ../encoder_t.h ../motor_t.h ../robot_parameter.h
wheel_velocity_test.o: ../encoder_reader.h ../motor_velocity.h ../motor_pwm.h
