cmd_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o := unused

source_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o := src/isa/riscv32/inst.c

deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o := \
  src/isa/riscv32/local-include/reg.h \
    $(wildcard include/config/rt/check.h) \
  /home/ycy/ics2022/nemu/include/common.h \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/ycy/ics2022/nemu/include/macro.h \
  /home/ycy/ics2022/nemu/include/debug.h \
  /home/ycy/ics2022/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/ycy/ics2022/nemu/include/cpu/cpu.h \
  /home/ycy/ics2022/nemu/include/cpu/ifetch.h \
  /home/ycy/ics2022/nemu/include/memory/vaddr.h \
  /home/ycy/ics2022/nemu/include/cpu/decode.h \
    $(wildcard include/config/itrace.h) \
  /home/ycy/ics2022/nemu/include/isa.h \
  /home/ycy/ics2022/nemu/src/isa/riscv32/include/isa-def.h \

/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o: $(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o)

$(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o):
