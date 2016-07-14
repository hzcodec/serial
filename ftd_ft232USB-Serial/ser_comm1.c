/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : ser_comm1.c
    Reference   : -
    Description : The program sends commands to ST7580 Power Line Modem.
                  
                  The protocol is a local frame format according to the following:
                  +------+---------+-----------+-------------------+-----------+
                  | STX  | Length  | Command   | Payload           | Checksum  |
                  +------+---------+-----------+-------------------+-----------+
		   
		   STX:      Start of text delimiter
		   Length:   Byte length of data field
		   Command:  Command type code
		   Payload:  Data to be sent
		   Checksum: Checksum calculated on lenght, command and payload, N.B! bytes are swapped


		  To communicate via a serial link use:
                    Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC
                    Red    - Vcc
                    Black  - GND
                    Brown  - CTS
                    Green  - RTS
                    Yellow - RxD
                    Orange - TxD


                  To check if, Ltd FT232 USB-Serial (UART) IC, is connected to USB:
		    > lsusb

		  This will give (N.B! devie ID may differ):
                      Bus 003 Device 004: ID 0403:6001 Future Technology Devices International,
		      Ltd FT232 USB-Serial (UART) IC

		  Also check port:
		    > ls /dev/ttyUSB*

		  This will give:
                      /dev/ttyUSB0


		  Ex. how to run:
                    ./ser_com1 1
                    ./ser_com1 2

                  <1> : create MIB_WriteRequest
                  <2> : create DL_DataRequest
                  <9> : create PingRequest


                  To compile:

		    manually:
                      gcc -std=gnu99 common.c -o common.o -c -I .
                      gcc -std=gnu99 uart.c -o uart.o -c -I .
                      gcc -std=gnu99 messages.c -o messages.o -c -I .
                      gcc -std=gnu99 ser_comm1.c -o ser_comm1.o -c -I .
                      gcc -std=gnu99 ser_comm1.o common.o uart.o messages.o -o ser_com1

		    or:
		      make


		  Test run:
		    A test run with v1.00 has been done. A result can be seen in figure
		    serial_comm1.PNG.

                    N.B! Using baud rate less than 57600 does not work. Due to that pin BR0/BR1 on
		    ST7580 is pulled up to VDDIO.
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

  int noBytes    = 0;  // number of bytes written
  int dataLength = 0;  // length of message data field
  Message msg;         // message structure according to the local frame format (see above)

  // Open up device for read/write and check status. NOCTTY - not controlling terminal
  fd = open(MODEM_DEVICE, O_RDWR | O_NOCTTY);
  if (fd < 0)
  {
    perror("Error, ttyUSB0 could not be opened!");
    exit(-1);
  }

  // if too few arguments then jump out
  if (argc < 2)
  {
    printf("To few arguments!\n");
    printf("<1> : create MIB_WriteRequest\n");
    printf("<2> : create DL_DataRequest with custom configuration - TX_GAIN=21\n");
    printf("<3> : create DL_DataRequest with custom configuration - TX_GAIN=31\n");
    printf("<4> : create DL_DataRequest with PHY configuration\n");
    printf("<9> : create PingRequest\n");
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
      dataLength = DL_DataRequest_LengthCustom;
      createDlDataRequestMessage1(&msg, dataLength);
      break;
    case 3:
      dataLength = DL_DataRequest_LengthCustom;
      createDlDataRequestMessage2(&msg, dataLength);
      break;
    case 4:
      dataLength = DL_DataRequest_LengthPhy;
      createDlDataRequestMessage3(&msg, dataLength);
      break;
    case 9:
      dataLength = PingRequest_Length;
      createPingRequestMessage(&msg, dataLength);
      break;
    default:
      perror("Input argument not valid!");
      exit(-1);
  }  

  configSerialPort(&serialPortSettings);
  openSerialPort(pSerialPortSettings);

  // check current output baud rate and print out result
  checkBaudRate(pSerialPortSettings);

  // RTS control
  toggleRTS(1);

  printMessage(&msg, dataLength+CHECKSUM_LENGTH);

  // write message to port
  noBytes = write(fd, &msg, HEADER_LENGTH+dataLength+CHECKSUM_LENGTH);
  printf(" \nTotal number of bytes sent=%d\n", noBytes);
  printf("+-------------------------------------------------------------------------------+\n");

  close(fd);

  return 0;
}
