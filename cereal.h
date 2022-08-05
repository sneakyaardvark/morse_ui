//
// Created by andrew on 8/4/22.
//

#ifndef _CEREAL_H_
#define _CEREAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h> // has file controls like O_RDWR
#include <errno.h> // error integer and strerror()
#include <termios.h> // POSIX terminal definitions
#include <unistd.h> // write(), read(), close()

int initSerial();

#endif //_CEREAL_H_
