//
// Created by andrew on 8/4/22.
//

#ifndef MORSE_UI_MORSE_FUNCTIONS_H
#define MORSE_UI_MORSE_FUNCTIONS_H

#include <ncurses.h>
#include <string.h>

// moo
extern const char cowsay[];

enum choices {MESSAGE, L_ON, L_OFF, EXIT};
extern const char *strChoice[];

void sendMessage(WINDOW *input_win);

void sendSerialMsg(const char *str);

#endif //MORSE_UI_MORSE_FUNCTIONS_H
