//
// Created by andrew on 8/4/22.
//

#include "morse_functions.h"

// moo
const char cowsay[] = {"o   ^__^\n"
                       " o  (oo)\\_______\n"
                       "    (__)\\       )\\/\\"
                       "        ||----w |\n"
                       "        ||     ||"};

const char *strChoice[] = { "MESSAGE", "LASER ON", "LASER OFF", "EXIT" };

void sendMessage(WINDOW *input_win)
{
    echo();
    char buff[255];
    wclear(input_win);
    mvwgetstr(input_win, 1, 1, buff);
    //sendSerialMsg(buff);
    noecho();
}

void sendSerialMsg(const char *str)
{

}