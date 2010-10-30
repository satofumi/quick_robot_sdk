/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-sh", "elf32-sh", "elf32-sh")
OUTPUT_ARCH(sh)
ENTRY(start)
SEARCH_DIR("/usr/share/gnush_v0803_elf-1/sh-elf/lib");

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = 0x0); . = 0xffffa000;

  .text :
  {
     _vec_top = . ;

     LONG(ABSOLUTE(start))                                         /* 0 */
     LONG(ABSOLUTE(_stack))                                        /* 1 */
     LONG(ABSOLUTE(start))                                         /* 2 */
     LONG(ABSOLUTE(_stack))                                        /* 3 */
     LONG(DEFINED(_futou1)?ABSOLUTE(_futou1):ABSOLUTE(start))      /* 4 */
   . += 4;                                                         /* 5 */
     LONG(DEFINED(_futou2)?ABSOLUTE(_futou2):ABSOLUTE(start))      /* 6 */
   . += 4*2;                                                       /* 7-8 */
     LONG(DEFINED(_adderr1)?ABSOLUTE(_adderr1):ABSOLUTE(start))    /* 9 */
   . += 4;                                                         /* 10 */
     LONG(DEFINED(_nmi)?ABSOLUTE(_nmi):ABSOLUTE(start))            /* 11 */
     LONG(DEFINED(_usr)?ABSOLUTE(_usr):ABSOLUTE(start))            /* 12 */
   . += 4*19;                                                      /* 13-31 */
   . += 4*32;                                                      /* 32-63 */
     LONG(DEFINED(_irq0)?ABSOLUTE(_irq0):ABSOLUTE(start))          /* 64 */
     LONG(DEFINED(_irq1)?ABSOLUTE(_irq1):ABSOLUTE(start))          /* 65 */
     LONG(DEFINED(_irq2)?ABSOLUTE(_irq2):ABSOLUTE(start))          /* 66 */
     LONG(DEFINED(_irq3)?ABSOLUTE(_irq3):ABSOLUTE(start))          /* 67 */
  . += 4*20;                                                       /* 68-87 */
     LONG(DEFINED(_tgia0)?ABSOLUTE(_tgia0):ABSOLUTE(start))        /* 88 */
     LONG(DEFINED(_tgib0)?ABSOLUTE(_tgib0):ABSOLUTE(start))        /* 89 */
     LONG(DEFINED(_tgic0)?ABSOLUTE(_tgic0):ABSOLUTE(start))        /* 90 */
     LONG(DEFINED(_tgid0)?ABSOLUTE(_tgid0):ABSOLUTE(start))        /* 91 */
     LONG(DEFINED(_tgiv0)?ABSOLUTE(_tgiv0):ABSOLUTE(start))        /* 92 */
     LONG(DEFINED(_tgie0)?ABSOLUTE(_tgie0):ABSOLUTE(start))        /* 93 */
     LONG(DEFINED(_tgif0)?ABSOLUTE(_tgif0):ABSOLUTE(start))        /* 94 */
  . += 4;                                                          /* 95 */
     LONG(DEFINED(_tgia1)?ABSOLUTE(_tgia1):ABSOLUTE(start))        /* 96 */
     LONG(DEFINED(_tgib1)?ABSOLUTE(_tgib1):ABSOLUTE(start))        /* 97 */
  . += 4*2;                                                        /* 98-99 */
     LONG(DEFINED(_tgiv1)?ABSOLUTE(_tgiv1):ABSOLUTE(start))        /* 100 */
     LONG(DEFINED(_tgiu1)?ABSOLUTE(_tgiu1):ABSOLUTE(start))        /* 101 */
  . += 4*2;                                                        /* 102-103 */
     LONG(DEFINED(_tgia2)?ABSOLUTE(_tgia2):ABSOLUTE(start))        /* 104 */
     LONG(DEFINED(_tgib2)?ABSOLUTE(_tgib2):ABSOLUTE(start))        /* 105 */
  . += 4*2;                                                        /* 106-107 */
     LONG(DEFINED(_tgiv2)?ABSOLUTE(_tgiv2):ABSOLUTE(start))        /* 108 */
     LONG(DEFINED(_tgiu2)?ABSOLUTE(_tgiu2):ABSOLUTE(start))        /* 109 */
  . += 4*2;                                                        /* 110-111 */
     LONG(DEFINED(_tgia3)?ABSOLUTE(_tgia3):ABSOLUTE(start))        /* 112 */
     LONG(DEFINED(_tgib3)?ABSOLUTE(_tgib3):ABSOLUTE(start))        /* 113 */
     LONG(DEFINED(_tgic3)?ABSOLUTE(_tgic3):ABSOLUTE(start))        /* 114 */
     LONG(DEFINED(_tgid3)?ABSOLUTE(_tgid3):ABSOLUTE(start))        /* 115 */
     LONG(DEFINED(_tgiv3)?ABSOLUTE(_tgiv3):ABSOLUTE(start))        /* 116 */
  . += 4*3;                                                        /* 117-119 */
     LONG(DEFINED(_tgia4)?ABSOLUTE(_tgia4):ABSOLUTE(start))        /* 120 */
     LONG(DEFINED(_tgib4)?ABSOLUTE(_tgib4):ABSOLUTE(start))        /* 121 */
     LONG(DEFINED(_tgic4)?ABSOLUTE(_tgic4):ABSOLUTE(start))        /* 122 */
     LONG(DEFINED(_tgid4)?ABSOLUTE(_tgid4):ABSOLUTE(start))        /* 123 */
     LONG(DEFINED(_tgiv4)?ABSOLUTE(_tgiv4):ABSOLUTE(start))        /* 124 */
  . += 4*3;                                                        /* 125-127 */
     LONG(DEFINED(_tgiu5)?ABSOLUTE(_tgiu5):ABSOLUTE(start))        /* 128 */
     LONG(DEFINED(_tgiv5)?ABSOLUTE(_tgiv5):ABSOLUTE(start))        /* 129 */
     LONG(DEFINED(_tgiw5)?ABSOLUTE(_tgiw5):ABSOLUTE(start))        /* 130 */
  . += 4;                                                          /* 131 */
     LONG(DEFINED(_oei1)?ABSOLUTE(_oei1):ABSOLUTE(start))          /* 132 */
     LONG(DEFINED(_oei3)?ABSOLUTE(_oei3):ABSOLUTE(start))          /* 133 */
  . += 4*50;                                                       /* 134-183 */
     LONG(DEFINED(_cmi0)?ABSOLUTE(_cmi0):ABSOLUTE(start))          /* 184 */
  . += 4*3;                                                        /* 185-187 */
     LONG(DEFINED(_cmi1)?ABSOLUTE(_cmi1):ABSOLUTE(start))          /* 188 */
  . += 4*7;                                                        /* 189-195 */
     LONG(DEFINED(_iti)?ABSOLUTE(_iti):ABSOLUTE(start))            /* 196 */
  . += 4*3;                                                        /* 197-199 */
     LONG(DEFINED(_adi0)?ABSOLUTE(_adi0):ABSOLUTE(start))          /* 200 */
     LONG(DEFINED(_adi1)?ABSOLUTE(_adi1):ABSOLUTE(start))          /* 201 */
  . += 4*14;                                                       /* 202-215 */
     LONG(DEFINED(_eri0)?ABSOLUTE(_eri0):ABSOLUTE(start))          /* 216 */
     LONG(DEFINED(_rxi0)?ABSOLUTE(_rxi0):ABSOLUTE(start))          /* 217 */
     LONG(DEFINED(_txi0)?ABSOLUTE(_txi0):ABSOLUTE(start))          /* 218 */
     LONG(DEFINED(_tei0)?ABSOLUTE(_tei0):ABSOLUTE(start))          /* 219 */
     LONG(DEFINED(_eri1)?ABSOLUTE(_eri1):ABSOLUTE(start))          /* 220 */
     LONG(DEFINED(_rxi1)?ABSOLUTE(_rxi1):ABSOLUTE(start))          /* 221 */
     LONG(DEFINED(_txi1)?ABSOLUTE(_txi1):ABSOLUTE(start))          /* 222 */
     LONG(DEFINED(_tei1)?ABSOLUTE(_tei1):ABSOLUTE(start))          /* 223 */
     LONG(DEFINED(_eri2)?ABSOLUTE(_eri2):ABSOLUTE(start))          /* 224 */
     LONG(DEFINED(_rxi2)?ABSOLUTE(_rxi2):ABSOLUTE(start))          /* 225 */
     LONG(DEFINED(_txi2)?ABSOLUTE(_txi2):ABSOLUTE(start))          /* 226 */
     LONG(DEFINED(_tei2)?ABSOLUTE(_tei2):ABSOLUTE(start))          /* 227 */
  }

  .interp         : { *(.interp) }
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rel.init       : { *(.rel.init) }
  .rela.init      : { *(.rela.init) }
  .rel.text       : { *(.rel.text .rel.text.* .rel.gnu.linkonce.t.*) }
  .rela.text      : { *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*) }
  .rel.fini       : { *(.rel.fini) }
  .rela.fini      : { *(.rela.fini) }
  .rel.rodata     : { *(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*) }
  .rela.rodata    : { *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*) }
  .rel.data.rel.ro : { *(.rel.data.rel.ro* .rel.gnu.linkonce.d.rel.ro.*) }
  .rela.data.rel.ro : { *(.rela.data.rel.ro* .rela.gnu.linkonce.d.rel.ro.*) }
  .rel.data       : { *(.rel.data .rel.data.* .rel.gnu.linkonce.d.*) }
  .rela.data      : { *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*) }
  .rel.tdata      : { *(.rel.tdata .rel.tdata.* .rel.gnu.linkonce.td.*) }
  .rela.tdata     : { *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*) }
  .rel.tbss       : { *(.rel.tbss .rel.tbss.* .rel.gnu.linkonce.tb.*) }
  .rela.tbss      : { *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*) }
  .rel.ctors      : { *(.rel.ctors) }
  .rela.ctors     : { *(.rela.ctors) }
  .rel.dtors      : { *(.rel.dtors) }
  .rela.dtors     : { *(.rela.dtors) }
  .rel.got        : { *(.rel.got) }
  .rela.got       : { *(.rela.got) }
  .rel.sdata      : { *(.rel.sdata .rel.sdata.* .rel.gnu.linkonce.s.*) }
  .rela.sdata     : { *(.rela.sdata .rela.sdata.* .rela.gnu.linkonce.s.*) }
  .rel.sbss       : { *(.rel.sbss .rel.sbss.* .rel.gnu.linkonce.sb.*) }
  .rela.sbss      : { *(.rela.sbss .rela.sbss.* .rela.gnu.linkonce.sb.*) }
  .rel.sdata2     : { *(.rel.sdata2 .rel.sdata2.* .rel.gnu.linkonce.s2.*) }
  .rela.sdata2    : { *(.rela.sdata2 .rela.sdata2.* .rela.gnu.linkonce.s2.*) }
  .rel.sbss2      : { *(.rel.sbss2 .rel.sbss2.* .rel.gnu.linkonce.sb2.*) }
  .rela.sbss2     : { *(.rela.sbss2 .rela.sbss2.* .rela.gnu.linkonce.sb2.*) }
  .rel.bss        : { *(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*) }
  .rela.bss       : { *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*) }
  .rel.plt        : { *(.rel.plt) }
  .rela.plt       : { *(.rela.plt) }
  .init           :
  {
    KEEP (*(.init))
  } =0
  .plt            : { *(.plt) }
  .text           :
  {
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
  } =0
  .fini           :
  {
    KEEP (*(.fini))
  } =0
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
  .rodata1        : { *(.rodata1) }
  .sdata2         :
  {
    *(.sdata2 .sdata2.* .gnu.linkonce.s2.*)
  }
  .sbss2          : { *(.sbss2 .sbss2.* .gnu.linkonce.sb2.*) }
  .eh_frame_hdr : { *(.eh_frame_hdr) }
  .eh_frame       : ONLY_IF_RO { KEEP (*(.eh_frame)) }
  .gcc_except_table   : ONLY_IF_RO { *(.gcc_except_table .gcc_except_table.*) }
  /* Adjust the address for the data segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = ALIGN(128) + (. & (128 - 1));
  /* Exception handling  */
  .eh_frame       : ONLY_IF_RW { KEEP (*(.eh_frame)) }
  .gcc_except_table   : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
  /* Thread Local Storage sections  */
  .tdata          : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss           : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
  .preinit_array  :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  .init_array     :
  {
     PROVIDE_HIDDEN (__init_array_start = .);
     KEEP (*(SORT(.init_array.*)))
     KEEP (*(.init_array))
     PROVIDE_HIDDEN (__init_array_end = .);
  }
  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  .ctors          :
  {
    ___ctors = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    ___ctors_end = .;
  }
  .dtors          :
  {
    ___dtors = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    ___dtors_end = .;
  }
  .jcr : { KEEP (*(.jcr)) }
  .data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro* .gnu.linkonce.d.rel.ro.*) }
  .dynamic        : { *(.dynamic) }
  _dynamic_end = .;
  .data           :
  {
    __data_start = .;
    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
  }
  .data1          : { *(.data1) }
  .got            : { *(.got.plt) *(.got) }
  /* We want the small data sections together, so single-instruction offsets
     can access them all, and initialized data all before uninitialized, so
     we can shorten the on-disk segment size.  */
  .sdata          :
  {
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }
  _edata = .; PROVIDE (edata = .);
  __bss_start = .;
  .sbss           :
  {
    *(.dynsbss)
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  }
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.
      FIXME: Why do we need it? When there is no .bss section, we don't
      pad the .data section.  */
   . = ALIGN(. != 0 ? 32 / 8 : 1);
  }
  . = ALIGN(32 / 8);
  . = ALIGN(32 / 8);
  _end = .; PROVIDE (end = .);
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .stack         (DEFINED(_stack) ? _stack : 0xffffbff0-0x10) (NOLOAD) :
  {
    _stack = .;
    *(.stack)
    LONG(0xdeaddead)
  }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) }
}
