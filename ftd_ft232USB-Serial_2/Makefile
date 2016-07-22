CC     = gcc
CFLAGS = -std=gnu99 -pedantic -Werror -Wall
#CFLAGS = -std=gnu99

p1: common.c
	$(CC) $(CFLAGS) common.c -o common.o -c -I .
	$(CC) $(CFLAGS) uart.c -o uart.o -c -I .
	$(CC) $(CFLAGS) messages.c -o messages.o -c -I .
	$(CC) $(CFLAGS) ser_comm1.c -o ser_comm1.o -c -I .
	$(CC) $(CFLAGS) ser_comm1.o common.o uart.o messages.o -o ser_com1

clean:
	rm -f ser_com1 *.o
