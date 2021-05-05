# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:
	(cd .. ; make)
	labDemo.elf
#additional rules for files
labDemo.elf: ${COMMON_OBJECTS} labDemo.o switches.o led.o p1_interrupt_handler.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: labDemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
