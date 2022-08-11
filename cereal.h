/*
 * ECE103 Engineering Computation
 * Team Wind
 * Philip Nevins
 * Andrew Stanton
 * Aziz Alshaaban
 * Luis Poroj
 * Paul Krueger
 * Author: Andrew Stanton
 * 8/1/2022
 * Serial communication to the microcontroller (header)
 *
 */

#ifndef _CEREAL_H_
#define _CEREAL_H_
#include <stdio.h>
#include <string.h>

#include <fcntl.h> // has file controls like O_RDWR
#include <errno.h> // error integer and strerror()
#include <termios.h> // POSIX terminal definitions
#include <unistd.h> // write(), read(), close()

// device control characters, used to for commands other than sending messages
extern const char DC1;
extern const char DC2;
extern const char DC3;
extern const char DC4;

/**
 * Open the serial port (/dev/ttyUSB0) and configure it
 * @return The file descriptor of the open port
 */
int initSerial();

#endif //_CEREAL_H_
