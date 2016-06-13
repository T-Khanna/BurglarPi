CC      = gcc
CFLAGS  = -Wall -g -D_BSD_SOURCE -std=gnu99 -Werror -pedantic
LDLIBS  = -lwiringPi -lwiringPiDev -lpthread -lm

.SUFFIXES: .c .o

.PHONY: clean 

burglarPi: burglarPi.o send_limit.o

clean:
	rm -f $(wildcard *.o) 
	rm -f burglarPi
