cmd_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o := unused

source_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o := src/cpu/cpu-exec.c

deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o := \
    $(wildcard include/config/itrace/cond.h) \
    $(wildcard include/config/itrace.h) \
    $(wildcard include/config/difftest.h) \
    $(wildcard include/config/isa/x86.h) \
    $(wildcard include/config/device.h) \
    $(wildcard include/config/target/am.h) \
  /home/ycy/ics2022/nemu/include/cpu/cpu.h \
  /home/ycy/ics2022/nemu/include/common.h \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/ycy/ics2022/nemu/include/macro.h \
  /home/ycy/ics2022/nemu/include/debug.h \
  /home/ycy/ics2022/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/ycy/ics2022/nemu/include/cpu/decode.h \
  /home/ycy/ics2022/nemu/include/isa.h \
  /home/ycy/ics2022/nemu/src/isa/riscv32/include/isa-def.h \
  /home/ycy/ics2022/nemu/include/cpu/difftest.h \
  /home/ycy/ics2022/nemu/include/difftest-def.h \
    $(wildcard include/config/isa/mips32.h) \
    $(wildcard include/config/isa/riscv32.h) \
    $(wildcard include/config/isa/riscv64.h) \

/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o: $(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o)

$(deps_/home/ycy/ics2022/nemu/build/obj-riscv32-nemu-interpreter/src/cpu/cpu-exec.o):
