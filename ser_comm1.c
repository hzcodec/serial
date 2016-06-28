/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : ser_comm1.c
    Reference   : -
    Description : Send serial data. Use argument to create message.
                  <1> : create MIB_WriteRequest
                  <2> : create PingRequest

		  Ex. how to run:
                    ./comm2 1
                    ./comm2 2


                  To compile:

		    manually:
                      gcc -std=gnu99 common.c -o common.o -c -I .
                      gcc -std=gnu99 uart.c -o uart.o -c -I .
                      gcc -std=gnu99 messages.c -o messages.o -c -I .
                      gcc -std=gnu99 ser_comm1.c -o ser_comm1.o -c -I .
                      gcc -std=gnu99 ser_comm1.o common.o uart.o messages.o -o ser_comm1

		    or:
		      make p1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* memcpy                            */
#include <fcntl.h>      /* File Control Definitions          */
#include <termios.h>    /* POSIX Terminal Control Definitions*/
#include <unistd.h>     /* UNIX Standard Definitions         */
#include <errno.h>      /* ERROR Number Definitions          */
#include <inttypes.h>   /* uint8_t                           */
#include <sys/ioctl.h>  /* rtsFlag = TIOCM_RTS               */ 

#include "common.h"
#include "uart.h"
#include "messages.h"

// global variables
int fd = -1;


int main(int argc, char* argv[])
{
  struct termios serialPortSettings;
  struct termios* pSerialPortSettings;
  pSerialPortSettings = &serialPortSettings;

  // number of bytes written
  int noBytes    = 0;  // number of bytes written
  int dataLength = 0;  // length of data
  Message msg;

  // if too few arguments then jump out
  if (argc < 2)
  {
    printf("To few arguments!\n");
    printf("<1> : create MIB_WriteRequest\n");
    printf("<2> : create PingRequest\n");
    exit(-1);
  }

  printHeadLine();

  // get input argument and convert to integer
  char* cSelectedCommand = argv[1];
  int selectedCommand = atoi(cSelectedCommand);

  // create message according to input argument
  switch(selectedCommand)
  {
    case 1:
      dataLength = MIB_WriteRequest_Length;
      createMibWriteRequestMessage(&msg, dataLength);
      break;
    case 2:
      dataLength = PingRequest_Length;
      createPingRequestMessage(&msg, dataLength);
      break;
    default:
      perror("Input argument not valid!");
      exit(-1);
  }  

  // Open up device for read/write and check status. NOCTTY - not controlling terminal
  fd = open(MODEM_DEVICE, O_RDWR | O_NOCTTY);
  if (fd < 0)
  {
    perror("Error, ttyUSB0 could not be opened!");
    exit(-1);
  }
  
  configSerialPort(&serialPortSettings);
  openSerialPort(pSerialPortSettings);

  // check current output baud rate and print out result
  checkBaudRate(pSerialPortSettings);

  // DTR control
  toggleDTR(ONE_SECOND);  // 1 s delay
  setDTR();

  printMessage(&msg, dataLength);

  // write message to port
  noBytes = write(fd, &msg, dataLength);
  printf(" \nNumber of bytes sent=%d\n", noBytes);

  close(fd);

  return 0;
}
