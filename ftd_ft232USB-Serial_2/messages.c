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

// Custom configuration - 8PSK = 0x2C, TX_GAIN = 31, payload data = 0x77, checksum = 0x0115
//uint8_t dataDlDataRequest_TxGain31[] = {0x2C, 0x1F, 0x77, 0x15, 0x01};


// request message with TX_GAIN=21 dB
void createMibWriteRequestMessage21dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=21 dB at ", KGRN);
  m->stx = PhysicalConfigurationObject21dB.stx;
  m->length = PhysicalConfigurationObject21dB.length;
  m->command = PhysicalConfigurationObject21dB.command;
  for (int i=0; i<(int)length+2; i++)
  {
    m->DataObject[i].field = PhysicalConfigurationObject21dB.DataObject[i].field;
    m->DataObject[i].data = PhysicalConfigurationObject21dB.DataObject[i].data;
  }
  
//  calculateChecksum(m->length, m->command, m->data);
}


// request message with TX_GAIN=31 dB
void createMibWriteRequestMessage31dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=21 dB at ", KGRN);
  m->stx = PhysicalConfigurationObject31dB.stx;
  m->length = PhysicalConfigurationObject31dB.length;
  m->command = PhysicalConfigurationObject31dB.command;
  for (int i=0; i<(int)length+2; i++)
  {
    m->DataObject[i].field = PhysicalConfigurationObject31dB.DataObject[i].field;
    m->DataObject[i].data = PhysicalConfigurationObject31dB.DataObject[i].data;
  }
  
//  calculateChecksum(m->length, m->command, m->data);
}

// custom message with TX_GAIN=21 dB
void createCustomRequestMessage21dB(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - TX_GAIN=21 dB at ", KGRN);
  m->stx = CustomConfigurationObject21dB.stx;
  m->length = CustomConfigurationObject21dB.length;
  m->command = CustomConfigurationObject21dB.command;
  for (int i=0; i<(int)length+2; i++)
  {
    m->DataObject[i].field = CustomConfigurationObject21dB.DataObject[i].field;
    m->DataObject[i].data = CustomConfigurationObject21dB.DataObject[i].data;
  }
  
//  calculateChecksum(m->length, m->command, m->data);
}


// custom message with TX_GAIN=21 dB
void createPhysicalRequestMessage(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - at ", KGRN);
  m->stx = PhysicalConfigurationObject.stx;
  m->length = PhysicalConfigurationObject.length;
  m->command = PhysicalConfigurationObject.command;
  for (int i=0; i<(int)length+2; i++)
  {
    m->DataObject[i].field = PhysicalConfigurationObject.DataObject[i].field;
    m->DataObject[i].data = PhysicalConfigurationObject.DataObject[i].data;
  }
  
//  calculateChecksum(m->length, m->command, m->data);
}


// ping message
void createPingMessage(Message* m, int length)
{
  printf("%sMessage: MIB_WriteRequest - at ", KGRN);
  m->stx = PingConfigurationObject.stx;
  m->length = PingConfigurationObject.length;
  m->command = PingConfigurationObject.command;
  for (int i=0; i<(int)length+2; i++)
  {
    m->DataObject[i].field = PingConfigurationObject.DataObject[i].field;
    m->DataObject[i].data = PingConfigurationObject.DataObject[i].data;
  }
  
//  calculateChecksum(m->length, m->command, m->data);
}

// request message with TX_GAIN=31 dB
//void createMibWriteRequestMessage31dB(Message* m, int length)
//{
//  printf("Message: MIB_WriteRequest - TX_GAIN=31 dB, Data=0x77\n");
//  m->stx      = 0x02;
//  m->length   = MIB_WriteRequest_Length;
//  m->command  = MIB_WriteRequest;
//  memcpy(m->data, dataMibWriteRequest31dB, sizeof(dataMibWriteRequest31dB));
//  
//  calculateChecksum(m->length, m->command, m->data);
//}
//
//
//// custom configuration, i.e TX_GAIN is a part of the message
//void createDlDataRequestMessage21dB(Message* m, int length)
//{
//  printf("Message: DL_DataRequest with Custom configuration of TX_GAIN=21 dB, Data=0x77\n");
//  m->stx      = 0x02;
//  m->length   = DL_DataRequest_LengthCustom;
//  m->command  = DL_DataRequest;
//  memcpy(m->data, dataDlDataRequest_TxGain21, sizeof(dataDlDataRequest_TxGain21));
//  
//  calculateChecksum(m->length, m->command, m->data);
//}
//
//
//// custom configuration, i.e TX_GAIN is a part of the message
//void createDlDataRequestMessage31dB(Message* m, int length)
//{
//  printf("Message: DL_DataRequest with Custom configuration of TX_GAIN=31 dB, Data=0x77\n");
//  m->stx      = 0x02;
//  m->length   = DL_DataRequest_LengthCustom;
//  m->command  = DL_DataRequest;
//  memcpy(m->data, dataDlDataRequest_TxGain31, sizeof(dataDlDataRequest_TxGain31));
//  
//  calculateChecksum(m->length, m->command, m->data);
//}
//
//
//// PHY configuration
//void createDlDataRequestMessagePhy(Message* m, int length)
//{
//  printf("Message: DL_DataRequest with PHY configuration of TX_GAIN\n");
//  m->stx      = 0x02;
//  m->length   = DL_DataRequest_LengthPhy;
//  m->command  = DL_DataRequest;
//  memcpy(m->data, dataDlDataRequest_PHY, sizeof(dataDlDataRequest_PHY));
//  
//  calculateChecksum(m->length, m->command, m->data);
//}
//
//
//void createPingRequestMessage(Message* m, int length)
//{
//  printf("Message: PingRequest\n");
//  m->stx      = 0x02;
//  m->length   = (uint8_t)PingRequest_Length;
//  m->command  = PingRequest;
//  memcpy(m->data, dataPingRequest, sizeof(dataPingRequest));
//
//  calculateChecksum(m->length, m->command, m->data);
//}

