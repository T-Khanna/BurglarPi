CC      = gcc
CFLAGS  = -Wall -g -D_BSD_SOURCE -std=gnu99 -Werror -pedantic -lwiringPi

.SUFFIXES: .c .o

.PHONY: clean 

burglarPi: test_buzzer.o

clean:
	rm -f $(wildcard *.o) 
	rm -f burglarPi
