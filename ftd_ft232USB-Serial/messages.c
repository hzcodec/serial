/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : messages.c
    Reference   : -
    Description : Create ST7580 messages.
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>   /* uint8_t */
#include <string.h>     /* memcpy  */
#include "common.h"


uint8_t dataMibWriteRequest21dB[] = {0x01,              // MIB object
                                     0x01, 0x4f, 0xf0,  // Hi freq
                                     0x01, 0x19, 0x40,  // Lo freq
                                     0x0e,              // RX mode, RX hi/lo channel mod, current ctrl
                                     0x15,              // TX gain = 21 dB
                                     0x00, 0x00,        // ZC dealy
                                     0x02,              // PSK preamble length
                                     0x35,              // FSK misc
                                     0x9b, 0x58,        // FSK msb/lsb unique word
	                             0xFF, 0x02};       // checksum

uint8_t dataMibWriteRequest31dB[] = {0x01,              // MIB object
                                     0x01, 0x4f, 0xf0,  // Hi freq
                                     0x01, 0x19, 0x40,  // Lo freq
                                     0x0e,              // RX mode, RX hi/lo channel mod, current ctrl
                                     0x1F,              // TX gain = 31 dB
                                     0x00, 0x00,        // ZC dealy
                                     0x02,              // PSK preamble length
                                     0x35,              // FSK misc
                                     0x9b, 0x58,        // FSK msb/lsb unique word
			             0x09, 0x03};       // checksum

// Custom configuration - 8PSK = 0x2C, TX_GAIN = 21, payload data = 0x77, checksum = 0x010B
uint8_t dataDlDataRequest_TxGain21[] = {0x2C, 0x15, 0x77, 0x0B, 0x01};

// Custom configuration - 8PSK = 0x2C, TX_GAIN = 31, payload data = 0x77, checksum = 0x0115
uint8_t dataDlDataRequest_TxGain31[] = {0x2C, 0x1F, 0x77, 0x15, 0x01};

// PHY configuration - 8PSK = 0x24, payload data = 0x77, checksum = 0x00ED
uint8_t dataDlDataRequest_PHY[] = {0x24,0x77, 0xED, 0x00};

// payload data, 0xdeadbeef
uint8_t dataPingRequest[] = {0xde, 0xad, 0xbe, 0xef};


void createMibWriteRequestMessage(Message* m, int length)
{
  printf("Message: MIB_WriteRequest with TX_GAIN=21 dB\n");
  m->stx      = 0x02;
  m->length   = MIB_WriteRequest_Length;
  m->command  = MIB_WriteRequest;
  memcpy(m->data, dataMibWriteRequest21dB, sizeof(dataMibWriteRequest21dB));
  
  calculateChecksum(m->length, m->command, m->data);
}

void createMibWriteRequestMessage31dB(Message* m, int length)
{
  printf("Message: MIB_WriteRequest with TX_GAIN=31 dB\n");
  m->stx      = 0x02;
  m->length   = MIB_WriteRequest_Length;
  m->command  = MIB_WriteRequest;
  memcpy(m->data, dataMibWriteRequest31dB, sizeof(dataMibWriteRequest31dB));
  
  calculateChecksum(m->length, m->command, m->data);
}


// custom configuration, i.e TX_GAIN is a part of the message
void createDlDataRequestMessage1(Message* m, int length)
{
  printf("Message: DL_DataRequest with Custom configuration of TX_GAIN=21 dB\n");
  m->stx      = 0x02;
  m->length   = DL_DataRequest_LengthCustom;
  m->command  = DL_DataRequest;
  memcpy(m->data, dataDlDataRequest_TxGain21, sizeof(dataDlDataRequest_TxGain21));
  
  calculateChecksum(m->length, m->command, m->data);
}

// custom configuration, i.e TX_GAIN is a part of the message
void createDlDataRequestMessage2(Message* m, int length)
{
  printf("Message: DL_DataRequest with Custom configuration of TX_GAIN=31 dB\n");
  m->stx      = 0x02;
  m->length   = DL_DataRequest_LengthCustom;
  m->command  = DL_DataRequest;
  memcpy(m->data, dataDlDataRequest_TxGain31, sizeof(dataDlDataRequest_TxGain31));
  
  calculateChecksum(m->length, m->command, m->data);
}

// PHY configuration
void createDlDataRequestMessage3(Message* m, int length)
{
  printf("Message: DL_DataRequest with PHY configuration of TX_GAIN\n");
  m->stx      = 0x02;
  m->length   = DL_DataRequest_LengthPhy;
  m->command  = DL_DataRequest;
  memcpy(m->data, dataDlDataRequest_PHY, sizeof(dataDlDataRequest_PHY));
  
  calculateChecksum(m->length, m->command, m->data);
}


void createPingRequestMessage(Message* m, int length)
{
  printf("Message: PingRequest\n");
  m->stx      = 0x02;
  m->length   = (uint8_t)PingRequest_Length;
  m->command  = PingRequest;
  memcpy(m->data, dataPingRequest, length);

  calculateChecksum(m->length, m->command, m->data);
}

