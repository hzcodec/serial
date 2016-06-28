#ifndef MESSAGES_H
#define MESSAGES_H

void createMibWriteRequestMessage(Message* m, int length);
void createDlDataRequestMessage(Message* m, int length);
void createPingRequestMessage(Message* m, int length);

#endif /* not defined MESSAGES_H */
