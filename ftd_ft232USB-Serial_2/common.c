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

// checksum calculated on lenght, command and payload
uint16_t calculateChecksum(Message* msg)
{
  uint16_t checkSum = 0x0000;

  // length and command
  checkSum = msg->length + msg->command;

  // now get payload also
  for (int i=0; i<(int)msg->length; i++)
  {
    checkSum += msg->data[i];
  }

  return checkSum;
}


// pretty headline ;-)
void printHeadLine()
{
  printf("\n%s+------------------------------------------------------------------------------------+\n", KYEL);
  printf("    _____ __ __ _  _     __                   __\n");                                   
  printf("   (_  |   /|_ (_)/ \\   (_  _  __ o  _  |    /   _ __ __    __  o  _  _ _|_ o  _ __\n"); 
  printf("   __) |  / __)(_)\\_/   __)(/_ |  | (_| |    \\__(_)|||||||_|| | | (_ (_| |_ | (_)| |\n");
  printf("\n+------------------------------------------------------------------------------------+%s\n", KNRM);
}


// print out the whole local frame format message in console
void printMessage(Message* msg, int length)
{
  printf("%s\n  -- Header --%s\n", KGRN, KNRM);
  printf("stx -     0x%02x\n", msg->stx);
  printf("Length -  0x%02x\n", msg->length);
  printf("Command - 0x%02x\n\n", msg->command);

  printf("%s  -- Payload --%s\n", KGRN, KNRM);
  for (int i=0; i<length; i++)
  {
    printf("[%2d] - %-10s : 0x%02x\n", i, msg->FieldName[i].field, msg->data[i]);
  }
}


void printHelp()
{
    printf("  <1> : send MIB_WriteRequest - TX_GAIN=21 dB\n");
    printf("  <2> : send MIB_WriteRequest - TX_GAIN=31 dB\n");
    printf("  <3> : send DL_DataRequest with custom configuration - TX_GAIN=21 dB\n");
    printf("  <4> : send DL_DataRequest with custom configuration - TX_GAIN=31 dB\n");
    printf("  <5> : send DL_DataRequest with PHY configuration\n");
    printf("  <9> : send PingRequest\n");
}

