#ifndef MESSAGES_H
#define MESSAGES_H

void createMibWriteRequestMessage21dB(Message* m, int length);
void createMibWriteRequestMessage31dB(Message* m, int length);
void createCustomRequestMessage21dB(Message* m, int length);
void createPhysicalRequestMessage(Message* m, int length);

void createDlDataRequestMessage31dB(Message* m, int length);
void createPingRequestMessage(Message* m, int length);

#endif /* not defined MESSAGES_H */
