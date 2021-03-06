# run_drive/test

CC = $(CXX)
CXXFLAGS = -DHOST_COMPILE -g -O0 -Wall -Werror $(INCLUDES)
INCLUDES = -I..

TARGET = \
	wheel_velocity_test \
	motor_table_pwm_test \
	velocity_control_test \

all : $(TARGET) test

clean :
	$(RM) $(TARGET) *.o all_test

depend :
	makedepend -Y -- $(INCLUDES) -- $(wildcard *.h *.cpp)

test : all_test
	./all_test

######################################################################
TEST_OBJS = all_test.o Connection_utilities_test.o connection_dummy.o connection_utilities.o std_string.o Run_commands_test.o protocol_handler.o run_commands.o htoi.o itoh.o isin_icos.o odometry_calculate.o imask.o


motor_table_pwm_test : motor_table_pwm.o

motor_table_pwm.o : ../motor_table_pwm.c
	$(CXX) $(CXXFLAAGS) $< -c -o $@


velocity_control_test : isqrt.o


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

itoh.o : ../itoh.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

isqrt.o : ../isqrt.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

isin_icos.o : ../isin_icos.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

odometry_calculate.o : ../odometry_calculate.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

imask.o : ../imask.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

# DO NOT DELETE

Connection_utilities_test.o: Connection_utilities_test.h
Connection_utilities_test.o: ../connection_utilities.h host_connection.h
Connection_utilities_test.o: ../connection.h
Run_commands_test.o: Run_commands_test.h host_connection.h
Run_commands_test.o: ../connection_utilities.h ../connection.h
Run_commands_test.o: ../protocol_handler.h ../run_t.h ../controller_config.h
Run_commands_test.o: ../run_system_t.h ../odometry_t.h ../path_t.h
Run_commands_test.o: ../velocity_t.h ../wheel_t.h ../encoder_t.h ../motor_t.h
connection_dummy.o: ../connection.h
motor_table_pwm_test.o: ../motor_pwm.h ../motor_table_pwm.h
velocity_control_test.o: ../velocity_control.c ../velocity_control.h
velocity_control_test.o: ../velocity_t.h ../isqrt.h ../robot_parameter.h
wheel_velocity_test.o: ../wheel_velocity.c ../wheel_velocity.h ../wheel_t.h
wheel_velocity_test.o: ../encoder_t.h ../motor_t.h ../robot_parameter.h
wheel_velocity_test.o: ../encoder_reader.h ../motor_velocity.h ../motor_pwm.h
