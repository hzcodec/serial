/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : common.c
    Reference   : -
    Description : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "common.h"

void calculateChecksum(uint8_t length, uint8_t command, uint8_t* data)
{
  uint16_t checkSum = 0x0000;

  checkSum = checkSum + length + command;

  for (int i=0; i<(int)length; i++)
  {
    checkSum += data[i];
  }

  printf("Checksum=%04x\n", checkSum);
}


void printHeadLine()
{
  printf("\n+-------------------------+\n");
  printf("|    Serial Port Write    |\n");
  printf("+-------------------------+\n");
}

void printMessage(Message* msg, int length)
{
  printf(".......................\n");
  printf("STX - Length - Command\n");
  printf("0x%02x", msg->stx);
  printf("  0x%02x", msg->length);
  printf("     0x%02x\n\n", msg->command);
  printf("Payload\n");
  for (int i=0; i<length; i++)
  {
    printf("[%d] - 0x%02x\n", i, msg->data[i]);
  }
}

