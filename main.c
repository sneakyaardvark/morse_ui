#include <ncurses.h>
#include "morse_functions.h"
#include "cereal.h"

#define VERSION 0.030

int main()
{

    // initialize the screen
    initscr();

    cbreak();
    //raw();
    noecho();


    attron(A_BOLD);
    printw("MORSE UI v%.3f", VERSION);
    attroff(A_BOLD);

    WINDOW *send_box = newwin(5, 20, 2, 1); // lines, columns, beg_y, beg_x
    WINDOW *send_input = newwin(3, 18, 3, 2);
    WINDOW *info = newwin(6, 40, 2, 25);
    WINDOW *log = newwin(12, 40, 8, 25);
    WINDOW *cow = newwin(10, 20, 8, 1);
    refresh(); // refresh whole screen so it knows we created the window

    // send
    box(send_box, 0, 0);
    mvwprintw(send_box, 0, 1, "SEND");
    wrefresh(send_box);

    // info
    box(info, 0, 0);
    mvwprintw(info, 0, 1, "INFO");
    wrefresh(info);

    // log
    box(log, 0, 0);
    mvwprintw(log, 0, 1, "LOG");
    wrefresh(log);

    // cowsay
    mvwprintw(cow, 0, 0, "%s", cowsay);
    wrefresh(cow);

    // ready for input
    keypad(send_input, true);

    //int serialPort = initSerial();

    int curr_choice = 0;
    bool loop = true;

    while (loop)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (i == curr_choice)
            {
                wclear(send_input);
                wattron(send_input, A_REVERSE);
                mvwprintw(send_input, 1, 1, "%s", strChoice[curr_choice]);
                wattroff(send_input, A_REVERSE);
            }
        }

        int choice = wgetch(send_input);
        wprintw(info, "%c", choice);
        switch (choice)
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
                if (curr_choice == 4)
                    curr_choice = 3;
                break;
            default:
                break;
        }
        if (choice == 10)
            switch (curr_choice)
            {
                case MESSAGE:
                    sendMessage(send_input, 1);
                    break;
                case L_ON:
                    break;
                case L_OFF:
                    break;
                case EXIT:
                    loop = false;
                    break;
                default:
                    break;
            }
    }

    // end ncurses
    endwin();
    return 0;
}
