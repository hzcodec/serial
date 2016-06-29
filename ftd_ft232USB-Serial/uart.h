#ifndef UART_H
#define UART_H


/*!
 * @brief  Set DTR
 *
 */
void setDTR();


/*!
 * @brief  Set DTR
 *
 * @param[in] timeValue     Delay time in s.
 * @retval rv   Successful.
 *
 */
int toggleDTR(int timeValue);


void setDTR();
int toggleDTR(int timeValue);
int setRTS(int rtsValue);
int toggleRTS(int timeValue);
void openSerialPort(struct termios* portSettings);
void configSerialPort(struct termios* portSettings);
void checkBaudRate(struct termios* portSettings);

#endif /* not defined COMMON_H */
