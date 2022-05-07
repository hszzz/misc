.PHONY : all clean

AS := nasm
CC := gcc
RM := rm -rf

CFLAGS  := -fcf-protection=none -mmanual-endbr -m32 -g
ASFLAGS := -f elf32

TARGET := test
CFILE  := main.c
AFILE  := func.asm

COUT := main.o
AOUT := func.o

all : $(TARGET)

$(TARGET) : $(AOUT) $(COUT)
	$(CC) $^ -o $@ $(CFLAGS)

$(COUT) : $(CFILE)
	$(CC) $(CFLAGS) -c $^ -o $@

$(AOUT) : $(AFILE)
	$(AS) $^ -o $@ $(ASFLAGS)

clean:
	$(RM) $(TARGET) $(COUT) $(AOUT)

