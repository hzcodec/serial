/* 
    Auther      : Heinz Samuelsson
    Date        : mån 20 jun 2016 14:10:48 CEST
    File        : uart.c
    Reference   : -
    Description : Configuration of UART.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      /* File Control Definitions           */
#include <termios.h>    /* POSIX Terminal Control Definitions */
#include <unistd.h>     /* UNIX Standard Definitions          */
#include <errno.h>      /* ERROR Number Definitions           */
#include <inttypes.h>   /* uint8_t                            */
#include <sys/ioctl.h>  /* rtsFlag = TIOCM_RTS                */ 
#include "common.h"

extern int fd;

// set data terminal ready
void setDTR()
{
  //int rv;
  int status;

  ioctl(fd, TIOCMGET, &status);
  printf("Set DTR high status=%d\n", status);
  status &= ~TIOCM_DTR;

  //rv = ioctl(fd, TIOCMSET, &status);
  ioctl(fd, TIOCMSET, &status);
}


// toggle data terminal ready
int toggleDTR(int timeValue)
{
  int rv;
  int status;

  ioctl(fd, TIOCMGET, &status);

  status &= ~TIOCM_DTR;
  rv = ioctl(fd, TIOCMSET, &status);
  sleep(1);

  status |= TIOCM_DTR;
  rv = ioctl(fd, TIOCMSET, &status);
  sleep(1);

  return rv;
}


// set reqest to send
int setRTS(int rtsValue)
{
  int rv;
  int rtsFlag = TIOCM_RTS; // modem constant for RTS pin

  if(rtsValue == 1)
  {
    rv = ioctl(fd, TIOCMBIS, &rtsFlag);
  }
  else
  {
    rv = ioctl(fd, TIOCMBIC, &rtsFlag);
  }
  return rv;
}


int toggleRTS(int timeValue)
{
  int rv;
  int rtsFlag = TIOCM_RTS; // modem constant for RTS pin

  rv = ioctl(fd, TIOCMBIS, &rtsFlag);
  usleep(timeValue);
  rv = ioctl(fd, TIOCMBIC, &rtsFlag);
  usleep(timeValue);
  return rv;
}


void openSerialPort(struct termios* portSettings)
{

  portSettings->c_cflag &= ~PARENB;                  // no parity bit
  portSettings->c_cflag &= ~CSTOPB;                  // stop bits = 1
  portSettings->c_cflag &= ~CSIZE;                   // clear mask
  portSettings->c_cflag &= ~CS8;                     // 8 data bits
  portSettings->c_cflag &= ~CRTSCTS;                 // turn of flow control
  portSettings->c_cflag &= ~(IXON | IXOFF | IXANY);  // turn off sw based flow control
  portSettings->c_cflag |= CBAUDEX;                  // enable baud rate 57600

  // TCIFLUSH  - flush data received but not read
  // TCOFLUSH  - flush data written but not transmitted
  // TCIOFLUSH - flush both
  if ((tcflush(fd, TCIOFLUSH) < 0) | (tcflush(fd, TCIFLUSH <0)))
  {
    perror("Error, flush not completed!");
    exit(-1);
  }
}

void configSerialPort(struct termios* portSettings)
{
  // get port parameters
  tcgetattr(fd, portSettings);

  // set output baud rate
  cfsetospeed(portSettings, B57600);

  // all changes done immediately
  int rv = tcsetattr(fd, TCSANOW, portSettings);
  if (rv < 0)
  {
    perror("Error, Could not get attributes!");
    exit(-1);
  }
}


void checkBaudRate(struct termios* portSettings)
{
  char *outputSpeed = "unknown";

  int baudRate = cfgetospeed(portSettings);

  switch (baudRate) {
     case B0:      outputSpeed = "none"; break;
     case B50:     outputSpeed = "50 Baud"; break;
     case B110:    outputSpeed = "110 Baud"; break;
     case B134:    outputSpeed = "134 Baud"; break;
     case B150:    outputSpeed = "150 Baud"; break;
     case B200:    outputSpeed = "200 Baud"; break;
     case B300:    outputSpeed = "300 Baud"; break;
     case B600:    outputSpeed = "600 Baud"; break;
     case B1200:   outputSpeed = "1200 Baud"; break;
     case B1800:   outputSpeed = "1800 Baud"; break;
     case B2400:   outputSpeed = "2400 Baud"; break;
     case B4800:   outputSpeed = "4800 Baud"; break;
     case B9600:   outputSpeed = "9600 Baud"; break;
     case B19200:  outputSpeed = "19200 Baud"; break;
     case B38400:  outputSpeed = "38400 Baud"; break;
     case B57600:  outputSpeed = "57600 Baud"; break;
  }
  printf("%sOutput Baud rate : %s %s\n", KGRN, outputSpeed, KNRM);
}


