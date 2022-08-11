/*
 * ECE103 Engineering Computation
 * Team Wind
 * Philip Nevins
 * Andrew Stanton
 * Aziz Alshaaban
 * Luis Poroj
 * Paul Krueger
 * Author: Andrew Stanton
 * 8/4/2022
 * Helper functions for the UI backend
 *
 */

#include "morse_functions.h"

// moo
const char cowsay[] = {"o   ^__^\n"
                       " o  (oo)\\_______\n"
                       "    (__)\\       )\\/\\"
                       "        ||----w |\n"
                       "        ||     ||"};

const char *strChoice[] = { "MESSAGE", "LASER ON", "LASER OFF", "TEST MSG", "EXIT" };

void sendMessage(WINDOW *input_win, int fd)
{
  echo(); // echo whatever the user types, until noecho()
  char buff[255];
  wclear(input_win); // clear the window
  mvwgetstr(input_win, 1, 1, buff); // get a string from the user
  noecho();
  sendSerialMsg(buff, fd);
}

void sendSerialMsg(const char *str, int fd)
{
  char msg[strlen(str)];
  strcpy(msg, str); // copy to the terminal character
  write(fd, msg, sizeof(msg)); // write the message to serial
}

void sendCmd(char cmd, int fd)
{
  write(fd, &cmd, sizeof(cmd));
}

void addLog(const char *str, WINDOW *log_win, int *cur_line)
{
  if (*cur_line == 11)
  {
    wclear(log_win);
    box(log_win, 0, 0); // quick fix: ideally the text and border should be separate
    mvwprintw(log_win, 0, 1, "LOG");
    *cur_line = 1;
  }
  mvwprintw(log_win, *cur_line, 1, "%s", str);
  wrefresh(log_win);
  ++*cur_line;
}