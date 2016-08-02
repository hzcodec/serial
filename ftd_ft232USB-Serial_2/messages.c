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
                                            0x02, MIB_WriteRequest_Length, MIB_WriteRequest,  // header
                                            {0x01, 0x01, 0x4f, 0xf0, 0x01, 0x19, 0x40, 0x0e, 0x15, 0x00, 0x00, 0x02, 0x35, 0x9b, 0x58, 0xff, 0x02}, // payload + checksum
                                            {
                                              {"MIB object"},  // field name of payload
                                              {"Hi freq"},
                                              {""},
                                              {""},
                                              {"Lo freq"},
                                              {""},
                                              {""},
                                              {"RX mode"},
                                              {"TX Gain"},
                                              {"ZC delay"},
                                              {""},
                                              {"PSK length"},
                                              {"FSK misc"},
                                              {"FSK msb"},
                                              {"FSK lsb"},
                                              {"Checksum"},
                                              {""},
                                           }
                                          };

Message PhysicalConfigurationObject31dB = {
                                            0x02, MIB_WriteRequest_Length, MIB_WriteRequest, // header
                                            {0x01, 0x01, 0x4f, 0xf0, 0x01, 0x19, 0x40, 0x0e, 0x1f, 0x00, 0x00, 0x02, 0x35, 0x9b, 0x58, 0x09, 0x03}, // payload + checksum
                                            {
                                              {"MIB object"}, // field names of payload
                                              {"Hi freq"},
                                              {""},
                                              {""},
                                              {"Lo freq"},
                                              {""},
                                              {""},
                                              {"RX mode"},
                                              {"TX Gain"},
                                              {"ZC delay"},
                                              {""},
                                              {"PSK length"},
                                              {"FSK misc"},
                                              {"FSK msb"},
                                              {"FSK lsb"},
                                              {"Checksum"},
                                              {""},
                                            }
                                          };

Message CustomConfigurationObject21dB = {
                                          0x02, DL_DataRequest_LengthCustom, DL_DataRequest, // header
                                          {0x2c, 0x15, 0x77, 0x0b, 0x01}, // payload + checksum
                                          {
                                            {"8PSK"},    // field names of payload
                                            {"TX Gain"},
                                            {"Payload"},
                                            {"Checksum"},
                                            {""},
                                          }
                                        };

Message CustomConfigurationObject31dB = {
                                          0x02, DL_DataRequest_LengthCustom, DL_DataRequest,  //header
                                          {0x2c, 0x1f, 0x77, 0x15, 0x01},                     //payload + checksum
                                          {
                                            {"8PSK"},                                        // field names of payload
                                            {"TX Gain"},
                                            {"Payload"},
                                            {"Checksum"},
                                            {""},
                                          }
                                        };

Message PhysicalConfigurationObject = {
                                        0x02, DL_DataRequest_LengthPhy, DL_DataRequest, // header 
                                        {0x24, 0x77, 0xed, 0x00},                       // payload + checksum
                                        {
				          {"8PSK"},                                     // field names of payload
				          {"Payload"}, 
				          {"Checksum"},
				          {""},      
				        }
                                      };

Message PingConfigurationObject = {
                                    0x02, PingRequest_Length, PingRequest, // header
                                    {0xde, 0xad, 0xbe, 0xef, 0x68, 0x03},  // payload + checksum
				    {
                                      {"Payload"},                         // field names of payload
                                      {""},
                                      {""},
                                      {""},
                                      {"Checksum"},
                                      {""},
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
    msg->data[i] = configObj.data[i];
    msg->FieldName[i].field = configObj.FieldName[i].field;
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

