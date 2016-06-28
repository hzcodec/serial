/* 
    Auther      : Heinz Samuelsson
    Date        : ons  8 jun 2016 10:10:56 CEST
    File        : messages.c
    Reference   : -
    Description : Create messages.
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>   /* uint8_t                           */
#include <string.h>     /* memcpy                            */
#include "common.h"


uint8_t dataMibWriteRequest[] = {0x01,              // MIB object
                                 0x01, 0x4f, 0xf0,  // Hi freq
                                 0x01, 0x19, 0x40,  // Lo freq
                                 0x0e,              // RX mode, RX hi/lo channel mod, current ctrl
                                 0x0a,              // TX gain
                                 0x00, 0x00,        // ZC dealy
                                 0x02,              // PSK preamblef length
                                 0x35,              // FSK misc
                                 0x9b,0x58};        // FSK msb/lsb unique word

//                           payload data
uint8_t dataPingRequest[] = {0xde, 0xad, 0xbe, 0xef};


void createMibWriteRequestMessage(Message* m, int length)
{
  printf("*** Message: MibWriteRequest ***\n");
  m->stx      = 0xa2;
  m->length   = 0x0f;
  m->command  = MIB_WriteRequest;
  memcpy(m->data, dataMibWriteRequest, length);
  
  calculateChecksum(m->length, m->command, m->data);
}


void createPingRequestMessage(Message* m, int length)
{
  printf("*** Message: PingRequest ***\n");
  m->stx      = 0x02;
  m->length   = 0x04;
  m->command  = PingRequest;
  memcpy(m->data, dataPingRequest, length);

  calculateChecksum(m->length, m->command, m->data);
}

