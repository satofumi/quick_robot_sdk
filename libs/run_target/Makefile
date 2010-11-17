# run_drive/

ARCH = sh-elf
SOURCE_DIR = .
include $(SOURCE_DIR)/build_rule.mk

RUBY = ruby

CFLAGS_FOR_BUILD = -DHOST_COMPILE -O2 -m2 -Wall -Werror -W $(INCLUDES_FOR_BUILD)
INCLUDES_FOR_BUILD =
LDFLAGS_FOR_BUILD = -nostartfiles $(START_UP_FOR_BUILD)
LDLIBS_FOR_BUILD = -L/usr/share/gnush/lib/gcc/sh-elf/4.5-GNUSH_v10.03/mrenesas/m2/ -lgcc-Os-4-200
#LDLIBS_FOR_BUILD =

START_UP_FOR_BUILD = $(SOURCE_DIR)/crt0.S
LD_LOAD_FOR_BUILD = $(SOURCE_DIR)/aki_sh7125_load.x
LD_ROM_FOR_BUILD = $(SOURCE_DIR)/aki_sh7125_rom.x


TARGET = \
	isin_icos.h isin_icos.c \
	run_drive.mot run_drive.rom run_drive.dis \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o
	cd samples/ && $(MAKE) clean
	cd test/ && $(MAKE) clean
	$(RM) -rf generated_html

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c)

.PHONY : all clean html upload
######################################################################
run_drive.mot run_drive.rom run_drive.dis : run_drive.o setup_state.o control_state.o pause_state.o clock_initialize.o imask.o run_system.o connection.o connection_utilities.o protocol_handler.o sci_interrupt_read_write.o emergency_io_control.o timer_control.o path_follow.o velocity_control.o body_control.o wheel_velocity.o motor_velocity.o motor_table_pwm.o motor_pwm.o encoder_reader.o odometry_calculate.o mtu2_initialize.o ring_buffer.o run_commands.o htoi.o itoh.o isin_icos.o isqrt.o #iatan2.o

isin_icos.c : create_isin_icos.rb
	$(RUBY) $< > $@ || $(RM) $@

isin_icos.h : create_isin_icos.rb
	$(RUBY) $< header > $@ || $(RM) $@

isin_icos.o : isin_icos.h

iatan2.c : create_iatan2.rb
	$(RUBY) $< > $@ || $(RM) $@

iatan2.o : iatan2.h


# DO NOT DELETE

body_control.o: wheel_t.h encoder_t.h motor_t.h
control_state.o: run_t.h controller_config.h run_system_t.h odometry_t.h
control_state.o: path_t.h velocity_t.h wheel_t.h encoder_t.h motor_t.h
encoder_reader.o: encoder_t.h
motor_table_pwm.o: motor_pwm.h
motor_velocity.o: motor_t.h
odometry_calculate.o: odometry_t.h
path_follow.o: path_t.h velocity_t.h odometry_t.h
path_t.o: velocity_t.h
pause_state.o: run_t.h controller_config.h run_system_t.h odometry_t.h
pause_state.o: path_t.h velocity_t.h wheel_t.h encoder_t.h motor_t.h
protocol_handler.o: run_t.h controller_config.h run_system_t.h odometry_t.h
protocol_handler.o: path_t.h velocity_t.h wheel_t.h encoder_t.h motor_t.h
run_commands.o: run_t.h controller_config.h run_system_t.h odometry_t.h
run_commands.o: path_t.h velocity_t.h wheel_t.h encoder_t.h motor_t.h
run_system.o: run_system_t.h
run_t.o: controller_config.h run_system_t.h odometry_t.h path_t.h
run_t.o: velocity_t.h wheel_t.h encoder_t.h motor_t.h
setup_state.o: run_t.h controller_config.h run_system_t.h odometry_t.h
setup_state.o: path_t.h velocity_t.h wheel_t.h encoder_t.h motor_t.h
velocity_control.o: velocity_t.h
wheel_t.o: encoder_t.h motor_t.h
wheel_velocity.o: wheel_t.h encoder_t.h motor_t.h
body_control.o: body_control.h wheel_t.h encoder_t.h motor_t.h
body_control.o: wheel_velocity.h controller_config.h robot_parameter.h
clock_initialize.o: clock_initialize.h
connection.o: connection.h sci_read_write.h interrupt_priority.h
connection_utilities.o: connection_utilities.h connection.h std_string.h
control_state.o: control_state.h run_t.h controller_config.h run_system_t.h
control_state.o: odometry_t.h path_t.h velocity_t.h wheel_t.h encoder_t.h
control_state.o: motor_t.h imask.h interrupt_priority.h robot_parameter.h
control_state.o: pause_state.h emergency_io_control.h timer_control.h
control_state.o: protocol_handler.h run_system.h encoder_reader.h
control_state.o: odometry_calculate.h path_follow.h body_control.h
control_state.o: wheel_velocity.h
emergency_io_control.o: emergency_io_control.h
encoder_reader.o: encoder_reader.h encoder_t.h mtu2_initialize.h
htoi.o: htoi.h
iatan2.o: iatan2.h
imask.o: imask.h
isin_icos.o: isin_icos.h
isqrt.o: isqrt.h
itoh.o: itoh.h
motor_pwm.o: motor_pwm.h mtu2_initialize.h
motor_table_pwm.o: motor_table_pwm.h motor_pwm.h
motor_velocity.o: motor_velocity.h motor_t.h robot_parameter.h
motor_velocity.o: motor_table_pwm.h motor_pwm.h encoder_reader.h encoder_t.h
mtu2_initialize.o: mtu2_initialize.h
odometry_calculate.o: odometry_calculate.h odometry_t.h robot_parameter.h
odometry_calculate.o: controller_config.h isin_icos.h
path_follow.o: path_follow.h path_t.h velocity_t.h odometry_t.h
path_follow.o: velocity_control.h robot_parameter.h isqrt.h
path_follow.o: odometry_calculate.h isin_icos.h
pause_state.o: pause_state.h run_t.h controller_config.h run_system_t.h
pause_state.o: odometry_t.h path_t.h velocity_t.h wheel_t.h encoder_t.h
pause_state.o: motor_t.h emergency_io_control.h wheel_velocity.h
protocol_handler.o: protocol_handler.h run_t.h controller_config.h
protocol_handler.o: run_system_t.h odometry_t.h path_t.h velocity_t.h
protocol_handler.o: wheel_t.h encoder_t.h motor_t.h connection.h
protocol_handler.o: connection_utilities.h run_commands.h std_string.h
ring_buffer.o: ring_buffer.h
run_commands.o: run_commands.h run_t.h controller_config.h run_system_t.h
run_commands.o: odometry_t.h path_t.h velocity_t.h wheel_t.h encoder_t.h
run_commands.o: motor_t.h htoi.h itoh.h wheel_velocity.h connection.h
run_commands.o: odometry_calculate.h update_parameter_id.h
run_drive.o: setup_state.h run_t.h controller_config.h run_system_t.h
run_drive.o: odometry_t.h path_t.h velocity_t.h wheel_t.h encoder_t.h
run_drive.o: motor_t.h control_state.h
run_system.o: run_system.h run_system_t.h
sci_interrupt_read_write.o: sci_read_write.h imask.h cpu_clock.h
sci_interrupt_read_write.o: ring_buffer.h
sci_read_write.o: sci_read_write.h cpu_clock.h
sci_utilities.o: sci_utilities.h sci_read_write.h
setup_state.o: setup_state.h run_t.h controller_config.h run_system_t.h
setup_state.o: odometry_t.h path_t.h velocity_t.h wheel_t.h encoder_t.h
setup_state.o: motor_t.h imask.h clock_initialize.h timer_control.h
setup_state.o: run_system.h emergency_io_control.h odometry_calculate.h
setup_state.o: path_follow.h wheel_velocity.h protocol_handler.h
setup_state.o: interrupt_priority.h
std_string.o: std_string.h
timer_control.o: timer_control.h cpu_clock.h
velocity_control.o: velocity_control.h velocity_t.h isqrt.h robot_parameter.h
wheel_velocity.o: wheel_velocity.h wheel_t.h encoder_t.h motor_t.h
wheel_velocity.o: robot_parameter.h encoder_reader.h motor_velocity.h
wheel_velocity.o: motor_pwm.h
