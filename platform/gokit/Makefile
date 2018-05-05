TARGET=stm32test

all: stm32tst 


CONTIKI=../..

CONTIKI_TARGET_MAIN=contiki-main.c

#PROJECT_SOURCEFILES = parity.c 


randgen: randgen.c
	gcc -DNDEBUG -I $(CONTIKI)/cpu/arm/stm32f103/ -I . -I $(CONTIKI)/core  randgen.c -o randgen

randcheck: randcheck.c
	gcc -DNDEBUG -I $(CONTIKI)/cpu/arm/stm32f103/ -I . -I $(CONTIKI)/core  randcheck.c -o randcheck

clean: gokit_clean

.PHONY: gokit_clean

gokit_clean:

include $(CONTIKI)/Makefile.include

