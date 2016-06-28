#ifndef COMMON_H
#define COMMON_H

// define commands
#define MIB_WriteRequest        0x08
#define PingRequest             0x2c
#define MIB_WriteRequest_Length 15
#define PingRequest_Length      4

#define MAX_DATA_MESSAGE_SIZE 25
#define MODEM_DEVICE "/dev/ttyUSB0"

#define ONE_SECOND 1

// data structure of message
typedef struct {
   uint8_t stx;      // start of text delimiter
   uint8_t length;   // length of data field
   uint8_t command;  // command type
   uint8_t data[MAX_DATA_MESSAGE_SIZE]; // data
} Message;


void calculateChecksum(uint8_t length, uint8_t command, uint8_t* data);
void printHeadLine();
void printMessage(Message* msg, int length);

#endif /* not defined COMMON_H */
