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
	sci_interrupt_write.mot sci_interrupt_write.rom \
	sci_interrupt_echoback.mot sci_interrupt_echoback.rom \

all : $(TARGET)

clean :
	$(RM) $(TARGET) *.o

depend :
	makedepend -Y -- $(INCLUDES_FOR_BUILD) -- $(wildcard *.h *.c)

.PHONY : all clean depend
######################################################################
BASE_OBJ = $(SOURCE_DIR)/clock_initialize.o $(SOURCE_DIR)/imask.o

sci_write.mot sci_write.rom : sci_write.o $(BASE_OBJ) $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/sci_read_write.o
sci_echoback.mot : sci_echoback.o $(BASE_OBJ) $(SOURCE_DIR)/sci_read_write.o
timer_1sec.mot timer_1sec.dis : timer_1sec.o $(BASE_OBJ) $(SOURCE_DIR)/timer_control.o itoa.o $(SOURCE_DIR)/std_string.o $(SOURCE_DIR)/sci_read_write.o
encoder_print.mot : encoder_print.o $(BASE_OBJ) $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/sci_read_write.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/motor_pwm.o
motor_pwm_out.mot : motor_pwm_out.o $(BASE_OBJ) $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/mtu2_initialize.o
motor_velocity_run.mot : motor_velocity_run.o $(BASE_OBJ) $(SOURCE_DIR)/timer_control.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/motor_velocity.o $(SOURCE_DIR)/mtu2_initialize.o
pwm_output.mot : pwm_output.o $(SOURCE_DIR)/pwm_control.o
wheel_velocity_run.mot : wheel_velocity_run.o $(BASE_OBJ) $(SOURCE_DIR)/wheel_velocity.o $(SOURCE_DIR)/encoder_reader.o $(SOURCE_DIR)/motor_velocity.o $(SOURCE_DIR)/mtu2_initialize.o $(SOURCE_DIR)/motor_pwm.o $(SOURCE_DIR)/timer_control.o
sci_interrupt_write.mot sci_interrupt_write.rom : sci_interrupt_write.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/sci_utilities.o $(SOURCE_DIR)/ring_buffer.o
sci_interrupt_echoback.mot sci_interrupt_echoback.rom : sci_interrupt_echoback.o $(BASE_OBJ) $(SOURCE_DIR)/sci_interrupt_read_write.o $(SOURCE_DIR)/ring_buffer.o

# DO NOT DELETE

encoder_print.o: ../imask.h ../clock_initialize.h ../interrupt_priority.h
encoder_print.o: ../encoder_reader.h ../encoder_t.h ../sci_read_write.h
encoder_print.o: ../sci_utilities.h ../motor_pwm.h
itoa.o: itoa.h
motor_pwm_out.o: ../clock_initialize.h ../motor_pwm.h
motor_velocity_run.o: ../clock_initialize.h ../imask.h
motor_velocity_run.o: ../interrupt_priority.h ../motor_velocity.h
motor_velocity_run.o: ../motor_t.h ../timer_control.h ../encoder_reader.h
motor_velocity_run.o: ../encoder_t.h ../robot_parameter.h
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
