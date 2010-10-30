# Compiler settings
CC_FOR_BUILD = $(ARCH)-gcc
CXX_FOR_BUILD = $(ARCH)-g++
AS_FOR_BUILD = $(ARCH)-as
LD_FOR_BUILD = $(ARCH)-ld
AR_FOR_BUILD = $(ARCH)-ar
OBJ_COPY_FOR_BUILD = $(ARCH)-objcopy
OBJ_DUMP_FOR_BUILD = $(ARCH)-objdump

# Suffix rules
.SUFFIXES :
.SUFFIXES : .rom .mot .dis .cof .o .c .h .S

.c.o:
	$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) -c $< -o $@

.S.o:
	$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) -c $<

%.mot:
	$(CC_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -T $(LD_LOAD_FOR_BUILD) $^ -o $@.tmp $(LDLIBS_FOR_BUILD)
	$(OBJ_COPY_FOR_BUILD) -O srec $@.tmp $@
	@$(RM) $@.tmp
	@chmod a-x $@

%.dis:
	$(CC_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -T $(LD_ROM_FOR_BUILD) $^ -o $@.tmp $(LDLIBS_FOR_BUILD)
	$(OBJ_DUMP_FOR_BUILD) -D --disassemble-zeroes $@.tmp > $@
	@$(RM) $@.tmp
	@chmod a-x $@

%.rom:
	$(CC_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -T $(LD_ROM_FOR_BUILD) $^ -o $@.tmp $(LDLIBS_FOR_BUILD)
	$(OBJ_COPY_FOR_BUILD) -O srec $@.tmp $@
	@$(RM) $@.tmp
	@chmod a-x $@

(%): %
	$(AR_FOR_BUILD) rv $(ARFLAGS_FOR_BUILD) $@ $<
