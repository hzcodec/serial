#ifndef COMMON_H
#define COMMON_H

#define CHECKSUM_LENGTH 2
#define HEADER_LENGTH   3

// define commands for the local frame format
#define MIB_WriteRequest        0x08
#define MIB_WriteRequest_Length 0x0F

#define DL_DataRequest                0x50
#define DL_DataRequest_LengthCustom   0x03  // length of payload for custom configuration (checksum not included)
#define DL_DataRequest_LengthPhy      0x02  // length of payload for PHY configuration (checksum not included)

#define PingRequest        0x2c
#define PingRequest_Length 0x04 

// misc defines
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

typedef struct 
{
   uint8_t stx;      // start of text delimiter
   uint8_t length;   // length of data field
   uint8_t command;  // command type
   
   struct
   {
     char*  field;   // field name of payload data
     uint8_t data;   // payload data
   } DataObject[17];

} Message;


uint16_t calculateChecksum(Message* data);
void printHeadLine();
void printMessage(Message* msg, int length);
void printHelp();

#endif /* not defined COMMON_H */
