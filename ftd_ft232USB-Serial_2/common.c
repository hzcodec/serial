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

  printf("Calculated checksum: %04x\n\n", checkSum);
}


void printHeadLine()
{
  printf("\n%s+------------------------------------------------------------------------------------+\n",KYEL);
  printf("    _____ __ __ _  _     __                   __\n");                                   
  printf("   (_  |   /|_ (_)/ \\   (_  _  __ o  _  |    /   _ __ __    __  o  _  _ _|_ o  _ __\n"); 
  printf("   __) |  / __)(_)\\_/   __)(/_ |  | (_| |    \\__(_)|||||||_|| | | (_ (_| |_ | (_)| |\n");
  printf("\n+------------------------------------------------------------------------------------+%s\n",KNRM);
}


void printMessage(Message* msg, int length)
{
  printf(".......................\n");
  printf("STX - Length - Command\n");
  printf("0x%02x", msg->stx);
  printf("  0x%02x", msg->length);
  printf("     0x%02x\n\n", msg->command);
//  printf("Payload\n");
//  for (int i=0; i<length; i++)
//  {
//    printf("[%d] - 0x%02x\n", i, msg->data[i]);
//  }
}


void printHelp()
{
    printf("  <1> : create MIB_WriteRequest - TX_GAIN=21 dB\n");
    printf("  <2> : create MIB_WriteRequest - TX_GAIN=31 dB\n");
    printf("  <3> : create DL_DataRequest with custom configuration - TX_GAIN=21 dB\n");
    printf("  <4> : create DL_DataRequest with custom configuration - TX_GAIN=31 dB\n");
    printf("  <5> : create DL_DataRequest with PHY configuration\n");
    printf("  <9> : create PingRequest\n");
}

