/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : messages.c
    Reference   : -
    Description : Create ST7580 local frame format messages.
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>   /* uint8_t */
#include <string.h>     /* memcpy  */
#include "common.h"


Message PhysicalConfigurationObject21dB = {
                                            0x02, MIB_WriteRequest_Length, MIB_WriteRequest,
                                             {
                                               {"MIB object", 0x01},
                                               {"Hi freq",    0x01},
                                               {"",           0x4f},
                                               {"",           0xf0},
                                               {"Lo freq",    0x01},
                                               {"",           0x19},
                                               {"",           0x40},
                                               {"RX mode",    0x0e},
                                               {"TX Gain",    0x15},
                                               {"ZC delay",   0x00},
                                               {"",           0x00},
                                               {"PSK length", 0x02},
                                               {"FSK misc",   0x35},
                                               {"FSK msb",    0x9b},
                                               {"FSK lsb",    0x58},
                                               {"Checksum",   0xff},
                                               {"",           0x02},
                                             }
                                          };

Message PhysicalConfigurationObject31dB = {
                                            0x02, MIB_WriteRequest_Length, MIB_WriteRequest,
                                             {
                                               {"MIB object", 0x01},
                                               {"Hi freq",    0x01},
                                               {"",           0x4f},
                                               {"",           0xf0},
                                               {"Lo freq",    0x01},
                                               {"",           0x19},
                                               {"",           0x40},
                                               {"RX mode",    0x0e},
                                               {"TX Gain",    0x1f},
                                               {"ZC delay",   0x00},
                                               {"",           0x00},
                                               {"PSK length", 0x02},
                                               {"FSK misc",   0x35},
                                               {"FSK msb",    0x9b},
                                               {"FSK lsb",    0x58},
                                               {"Checksum",   0x09},
                                               {"",           0x03},
                                             }
                                          };

Message CustomConfigurationObject21dB = {
                                          0x02, DL_DataRequest_LengthCustom, DL_DataRequest,
                                           {
                                             {"8PSK",     0x2c},
                                             {"TX Gain",  0x15},
                                             {"Payload",  0x77},
                                             {"Checksum", 0x0b},
                                             {"",         0x01},
                                           }
                                        };

Message CustomConfigurationObject31dB = {
                                          0x02, DL_DataRequest_LengthCustom, DL_DataRequest,
                                           {
                                             {"8PSK",     0x2c},
                                             {"TX Gain",  0x1f},
                                             {"Payload",  0x77},
                                             {"Checksum", 0x15},
                                             {"",         0x01},
                                           }
                                        };

Message PhysicalConfigurationObject = {
                                        0x02, DL_DataRequest_LengthPhy, DL_DataRequest,
                                         {
                                           {"8PSK",     0x24},
                                           {"Payload",  0x77},
                                           {"Checksum", 0xed},
                                           {"",         0x00},
                                         }
                                      };

Message PingConfigurationObject = {
                                        0x02, PingRequest_Length, PingRequest,
                                         {
                                           {"Payload",  0xde},
                                           {"",         0xad},
                                           {"",         0xbe},
                                           {"",         0xef},
                                           {"Checksum", 0x68},
                                           {"",         0x03},
                                         }
                                      };


// configure message
void configMessage(Message* msg, Message configObj, int length)
{
  msg->stx = configObj.stx;
  msg->length = configObj.length;
  msg->command = configObj.command;

  for (int i=0; i<(int)length+CHECKSUM_LENGTH; i++)
  {
    msg->DataObject[i].field = configObj.DataObject[i].field;
    msg->DataObject[i].data = configObj.DataObject[i].data;
  }
}


// request message with TX_GAIN=21 dB
void createMibWriteRequestMessage21dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=21 dB\n", KGRN);
  configMessage(m, PhysicalConfigurationObject21dB, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


// request message with TX_GAIN=31 dB
void createMibWriteRequestMessage31dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=31 dB\n", KGRN);
  configMessage(m, PhysicalConfigurationObject31dB, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


// custom message with TX_GAIN=21 dB
void createCustomRequestMessage21dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=21 dB\n", KGRN);
  configMessage(m, CustomConfigurationObject21dB, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


// custom message with TX_GAIN=31 dB
void createCustomRequestMessage31dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=31 dB\n", KGRN);
  configMessage(m, CustomConfigurationObject31dB, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


// physical message
void createPhysicalRequestMessage(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest\n", KGRN);
  configMessage(m, PhysicalConfigurationObject, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


// ping message
void createPingMessage(Message* m, int length)
{
  printf("%sMessage: PingRequest\n", KGRN);
  configMessage(m, PingConfigurationObject, length);

  uint16_t rv = calculateChecksum(m);
  printf("Calculated checksum: %04x\n", rv);
}


