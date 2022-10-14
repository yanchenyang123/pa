cmd_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o := unused

source_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o := src/engine/interpreter/hostcall.c

deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o := \
  /home/ycy/ics2022/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/ycy/ics2022/nemu/include/common.h \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/ycy/ics2022/nemu/include/macro.h \
  /home/ycy/ics2022/nemu/include/debug.h \
  /home/ycy/ics2022/nemu/include/cpu/ifetch.h \
  /home/ycy/ics2022/nemu/include/memory/vaddr.h \
  /home/ycy/ics2022/nemu/include/isa.h \
  /home/ycy/ics2022/nemu/src/isa/riscv32/include/isa-def.h \
  /home/ycy/ics2022/nemu/include/cpu/difftest.h \
    $(wildcard include/config/difftest.h) \
  /home/ycy/ics2022/nemu/include/difftest-def.h \
    $(wildcard include/config/isa/x86.h) \
    $(wildcard include/config/isa/mips32.h) \
    $(wildcard include/config/isa/riscv32.h) \
    $(wildcard include/config/isa/riscv64.h) \

/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o: $(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o)

$(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o):
