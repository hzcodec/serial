#ifndef COMMON_H
#define COMMON_H

// define commands
#define MIB_WriteRequest        0x08
#define MIB_WriteRequest_Length 15

#define PingRequest             0x2c
#define PingRequest_Length      4

#define MAX_DATA_MESSAGE_SIZE 25
#define MODEM_DEVICE "/dev/ttyUSB0"

#define ONE_SECOND 1

// define colors
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

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
