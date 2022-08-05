//
// Created by andrew on 8/4/22.
//

#include "cereal.h"

const unsigned char DC1 = 0b00010001;
const unsigned char DC2 = 0b00010010;
const unsigned char DC3 = 0b00010011;
const unsigned char DC4 = 0b00010100;

int initSerial()
{
  // on arduinos, it is often necessary to wait up to 2 seconds after opening / configuring the port
  // and possibly another 50ms or more between reads/writes

  // open the port
  int serialPort = open("/dev/ttyUSB0", O_RDWR);

  // new termios struct. tty seems to be conventional
  struct termios tty;

  // check errors from opening port
  if (serialPort < 0)
  {
    printf("Error %i from opening port: %s\n", errno, strerror(errno));
    exit(1);
  }

  // read existing settings and handle errors
  if (tcgetattr(serialPort, &tty) != 0)
  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    exit(1);
  }

  // configure tty
  // control modes
  tty.c_cflag &= ~PARENB; // clear (disable) parity bit
  tty.c_cflag &= ~CSTOPB; // clear stop (use only one stop bit, as is common)
  tty.c_cflag &= ~CSIZE; // clear all bits setting data size
  tty.c_cflag |= CS8; // 8 bits per byte. pretty standard
  tty.c_cflag &= ~CRTSCTS; // disable RTS/CTS hardware control (Ready To Send / Clear to Send; hardware specific)
  tty.c_cflag |= CREAD | CLOCAL; // turn on READ, disable modem control signals

  // local modes
  tty.c_lflag &= ~ICANON; // disable canonical mode (canonical mode process data line-by-line as newlines are received). This is obv undesirable for serial
  // these next three all have to do with echoing sent characters (this may not be necessary given canonical is disabled)
  tty.c_lflag &= ~ECHO; // no echo
  tty.c_lflag &= ~ECHOE; // no erasure
  tty.c_lflag &= ~ECHONL; // no newline echo
  tty.c_lflag &= ~ISIG; // disable INTR, QUIT, and SUSP

  // input modes
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off software flow control
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // disable any special handling of received data

  // output modes
  tty.c_oflag &= ~OPOST; // no special interpretation of output bytes (like newline chars)
  tty.c_oflag &= ~ONLCR; // no conversion of newline to CR/LF

  // if VMIN is 0, VTIME specifies time-out from start of read call
  // if VMIN > 0, VTIME specifies time-out from first received character
  tty.c_cc[VTIME] = 10; // wait up to 1 second (10 deciseconds), return as soon as any data is received
  tty.c_cc[VMIN] = 0;

  // set in/out baud rates
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  // save tty, check for errors
  if (tcsetattr(serialPort, TCSANOW, &tty) != 0)
  {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    exit(1);
  }

  return serialPort;
}