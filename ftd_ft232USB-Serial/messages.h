#ifndef MESSAGES_H
#define MESSAGES_H

void createMibWriteRequestMessage(Message* m, int length);
void createDlDataRequestMessage1(Message* m, int length);
void createDlDataRequestMessage2(Message* m, int length);
void createDlDataRequestMessage3(Message* m, int length);
void createPingRequestMessage(Message* m, int length);

#endif /* not defined MESSAGES_H */
