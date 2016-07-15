#ifndef MESSAGES_H
#define MESSAGES_H

void createMibWriteRequestMessage(Message* m, int length);
void createMibWriteRequestMessage31dB(Message* m, int length);
void createDlDataRequestMessage21dB(Message* m, int length);
void createDlDataRequestMessage31dB(Message* m, int length);
void createDlDataRequestMessagePhy(Message* m, int length);
void createPingRequestMessage(Message* m, int length);

#endif /* not defined MESSAGES_H */
