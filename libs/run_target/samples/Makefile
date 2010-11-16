# taiyaki/sample

ARCH = sh-elf
SOURCE_DIR = ..
include $(SOURCE_DIR)/build_rule.mk

CFLAGS_FOR_BUILD = -DHOST_COMPILE -O2 -m2 -Wall -Werror -W $(INCLUDES_FOR_BUILD)
INCLUDES_FOR_BUILD = -I$(SOURCE_DIR)
LDFLAGS_FOR_BUILD = -nostartfiles $(START_UP_FOR_BUILD)
LDLIBS_FOR_BUILD =

START_UP_FOR_BUILD = $(SOURCE_DIR)/crt0.S
LD_LOAD_FOR_BUILD = $(SOURCE_DIR)/aki_sh7125_load.x
LD_ROM_FOR_BUILD = $(SOURCE_DIR)/aki_sh7125_rom.x


TARGET = \
	sci_write.mot sci_write.rom \
	sci_echoback.mot \
	timer_1sec.mot \
	timer_1sec.dis \
	motor_pwm_out.mot \
	motor_velocity_run.mot \
	encoder_print.mot \
	wheel_velocity_run.mot \
	sci_interrupt_write.mot \
	sci_interrupt_echoback.mot \
	motor_table_record.mot motor_table_record.rom \
	circle_output.mot \
	odometry_print.mot \
	motor_control_graph.mot \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c)

.PHONY : all clean depend
######################################################################
BASE_OBJ = $(SOURCE_DIR)/clock_initialize.o $(SOURCE_DIR)/imask.o

$(SOURCE_DIR)/isin_icos.c $(SOURCE_DIR)/isin_icos.h :
	cd ../ && $(MAKE) isin_icos.h isin_icos.c

$(SOURCE_DIR)/isin_icos.o : $(SOURCE_DIR)/isin_icos.c $(SOURCE_DIR)/isin_icos.h

sci_write.mot sci_write.rom : sci_write.o $(BASE_OBJ) $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/sci_read_write.o
sci_echoback.mot : sci_echoback.o $(BASE_OBJ) $(SOURCE_DIR)/sci_read_write.o
timer_1sec.mot timer_1sec.dis : timer_1sec.o $(BASE_OBJ) $(SOURCE_DIR)/timer_control.o itoa.o $(SOURCE_DIR)/std_string.o $(SOURCE_DIR)/sci_read_write.o
encoder_print.mot : encoder_print.o $(BASE_OBJ) $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/sci_read_write.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/motor_pwm.o
motor_pwm_out.mot : motor_pwm_out.o $(BASE_OBJ) $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/mtu2_initialize.o
motor_velocity_run.mot : motor_velocity_run.o $(BASE_OBJ) $(SOURCE_DIR)/timer_control.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/motor_table_pwm.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/motor_velocity.o $(SOURCE_DIR)/mtu2_initialize.o
pwm_output.mot : pwm_output.o $(SOURCE_DIR)/pwm_control.o
wheel_velocity_run.mot : wheel_velocity_run.o $(BASE_OBJ) $(SOURCE_DIR)/wheel_velocity.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/motor_velocity.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/timer_control.o $(SOURCE_DIR)/motor_table_pwm.o
sci_interrupt_write.mot sci_interrupt_write.rom : sci_interrupt_write.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/ring_buffer.o
sci_interrupt_echoback.mot sci_interrupt_echoback.rom : sci_interrupt_echoback.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/ring_buffer.o
motor_table_record.mot motor_table_record.rom : motor_table_record.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/ring_buffer.o $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/mtu2_initialize.o
circle_output.mot : circle_output.o $(BASE_OBJ) $(SOURCE_DIR)/isin_icos.o $(SOURCE_DIR)/sci_read_write.o $(SOURCE_DIR)/sci_utilities.o
odometry_print.mot : odometry_print.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/timer_control.o $(SOURCE_DIR)/ring_buffer.o $(SOURCE_DIR)/isin_icos.o $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/odometry_calculate.o $(SOURCE_DIR)/motor_pwm.o
motor_control_graph.mot : motor_control_graph.o $(BASE_OBJ) $(SOURCE_DIR)/timer_control.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/motor_table_pwm.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/motor_velocity.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/ring_buffer.o $(SOURCE_DIR)/sci_utilities.o

# DO NOT DELETE

circle_output.o: ../imask.h ../clock_initialize.h ../interrupt_priority.h
circle_output.o: ../sci_read_write.h ../sci_utilities.h ../isin_icos.h
encoder_print.o: ../imask.h ../clock_initialize.h ../interrupt_priority.h
encoder_print.o: ../encoder_reader.h ../encoder_t.h ../sci_read_write.h
encoder_print.o: ../sci_utilities.h ../motor_pwm.h
itoa.o: itoa.h
motor_control_graph.o: ../clock_initialize.h ../imask.h
motor_control_graph.o: ../interrupt_priority.h ../motor_velocity.h
motor_control_graph.o: ../motor_t.h ../timer_control.h ../encoder_reader.h
motor_control_graph.o: ../encoder_t.h ../robot_parameter.h
motor_control_graph.o: ../sci_read_write.h ../sci_utilities.h
motor_pwm_out.o: ../clock_initialize.h ../motor_pwm.h
motor_table_record.o: ../imask.h ../clock_initialize.h
motor_table_record.o: ../interrupt_priority.h ../sci_read_write.h
motor_table_record.o: ../sci_utilities.h ../encoder_reader.h ../encoder_t.h
motor_table_record.o: ../motor_pwm.h
motor_velocity_run.o: ../clock_initialize.h ../imask.h
motor_velocity_run.o: ../interrupt_priority.h ../motor_velocity.h
motor_velocity_run.o: ../motor_t.h ../timer_control.h ../encoder_reader.h
motor_velocity_run.o: ../encoder_t.h ../robot_parameter.h
odometry_print.o: ../interrupt_priority.h ../sci_read_write.h
odometry_print.o: ../sci_utilities.h ../imask.h ../clock_initialize.h
odometry_print.o: ../timer_control.h ../odometry_calculate.h ../odometry_t.h
odometry_print.o: ../encoder_reader.h ../encoder_t.h ../controller_config.h
odometry_print.o: ../motor_pwm.h
sci_echoback.o: ../clock_initialize.h ../imask.h ../sci_read_write.h
sci_echoback.o: ../interrupt_priority.h
sci_interrupt_echoback.o: ../clock_initialize.h ../imask.h
sci_interrupt_echoback.o: ../sci_interrupt_read_write.h
sci_interrupt_echoback.o: ../interrupt_priority.h
sci_interrupt_write.o: ../clock_initialize.h ../imask.h
sci_interrupt_write.o: ../sci_interrupt_read_write.h ../sci_utilities.h
sci_interrupt_write.o: ../interrupt_priority.h
sci_write.o: ../clock_initialize.h ../imask.h ../sci_read_write.h
sci_write.o: ../sci_utilities.h ../interrupt_priority.h
timer_1sec.o: ../clock_initialize.h ../imask.h ../sci_read_write.h
timer_1sec.o: ../timer_control.h ../interrupt_priority.h itoa.h
timer_1sec.o: ../std_string.h
wheel_velocity_run.o: ../imask.h ../clock_initialize.h
wheel_velocity_run.o: ../interrupt_priority.h ../wheel_velocity.h
wheel_velocity_run.o: ../wheel_t.h ../encoder_t.h ../motor_t.h
wheel_velocity_run.o: ../encoder_reader.h ../timer_control.h
wheel_velocity_run.o: ../robot_parameter.h
