/*
 * Andrew Stanton
 * 7/14/2022
 * This is an NCURSES interface used to interact with a microcontroller
 * capable of sending morse code messages with a laser
 */

#include <ncurses.h>
#include "morse_functions.h"

#define VERSION 0.045

int main()
{
  initscr(); // initialize the screen

  cbreak(); // allows controls, like CTRL-C, as opposed to raw() which makes all input raw input
  noecho(); // do not echo what the user types

  attron(A_BOLD); // attribute on (bold)
  printw("MORSE UI v%.3f", VERSION);
  attroff(A_BOLD);

  WINDOW *send_box = newwin(5, 20, 2, 1); // lines, columns, beg_y, beg_x
  WINDOW *send_input = newwin(3, 18, 3, 2);
  WINDOW *info = newwin(6, 40, 2, 25);
  WINDOW *log = newwin(12, 40, 8, 25);
  WINDOW *cow = newwin(10, 20, 8, 1);
  refresh(); // refresh whole screen so it knows we created the windows

  // send
  box(send_box, 0, 0); // create a box, using default character set of 0,0
  mvwprintw(send_box, 0, 1, "SEND"); // print the title
  wrefresh(send_box); // refresh the window

  // info
  box(info, 0, 0);
  mvwprintw(info, 0, 1, "INFO");
  mvwprintw(info, 1, 1, "Select \"Message\" to type and send");

  wrefresh(info);

  // log
  box(log, 0, 0);
  mvwprintw(log, 0, 1, "LOG");
  wrefresh(log);
  int *log_mem = malloc(sizeof(int)); // keep track of which line to write the log to
  *log_mem = 1;

  // cowsay
  mvwprintw(cow, 0, 0, "%s", cowsay);
  wrefresh(cow);

  // now ready for input

  // enable keypad input (special keys like function #, arrows, etc
  keypad(send_input, true);

  int serialPort = initSerial();


  // add a mini menu in the 'send box' to select an action
  int curr_choice = 0;
  bool loop = true;

  while (loop)
  {
    for (int i = 0; i < 5; ++i)
    {
      if (i == curr_choice)
      {
        wclear(send_input);
        wattron(send_input, A_REVERSE);
        mvwprintw(send_input, 1, 1, "%s", strChoice[curr_choice]);
        wattroff(send_input, A_REVERSE);
      }
    }

    int key = wgetch(send_input);
    switch (key)
    {
      case KEY_UP:
      case (int) 'k':
        curr_choice--;
        if (curr_choice == -1)
          curr_choice = 0;
        break;
      case KEY_DOWN:
      case (int) 'j':
        curr_choice++;
        if (curr_choice == 5)
          curr_choice = 4;
        break;
      default:
        break;
    }
    if (key == 10) // user hits enter
      switch (curr_choice)
      {
        case MESSAGE:
          sendMessage(send_input, serialPort);
          addLog("Message sent", log, log_mem);
          break;
        case L_ON:
          sendCmd(DC1, serialPort);
          addLog("CMD: LASER ON", log, log_mem);
          break;
        case L_OFF:
          sendCmd(DC3, serialPort);
          addLog("CMD: LASER OFF", log, log_mem);
          break;
        case TEST:
          sendCmd(DC2, serialPort);
          addLog("CMD: TEST MSG", log, log_mem);
          break;
        case EXIT:
          addLog("EXITING...", log, log_mem);
          loop = false;
          break;
        default:
          break;
      }
  }

  close(serialPort);

  free(log_mem);

  // end ncurses
  endwin();
  return 0;
}
