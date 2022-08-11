/*
 * ECE103 Engineering Computation
 * Andrew Stanton / Team Wind
 * 8/4/2022
 * Helper functions for the UI backend (header)
 *
 */
#ifndef MORSE_UI_MORSE_FUNCTIONS_H
#define MORSE_UI_MORSE_FUNCTIONS_H

#include <ncurses.h>
#include <string.h>
#include <malloc.h>
#include "cereal.h"

// moo
extern const char cowsay[];

/**
 * Options for the action menu
 */
enum choices {MESSAGE, L_ON, L_OFF, TEST, EXIT};
/**
 * strings of the name of each action
 * in the action menu
 */
extern const char *strChoice[];

/**
 * Prompt the user for a string and send it using sendSerialMsg()
 * @param input_win
 * The window to prompt the user in, and echo their message
 * @param fd
 * File descriptor of the serial port
 * @see sendSerialMsg()
 */
void sendMessage(WINDOW *input_win, int fd);

/**
 * Format and send a message over serial
 * @param str
 * The message to send
 * @param fd
 * File desciptor of the serial port
 */
void sendSerialMsg(const char *str, int fd);

/**
 * Send a control character
 * @param cmd
 * The control the character
 * @param fd
 * File descriptor of the serial port
 */
void sendCmd(char cmd, int fd);

/**
 * Add an entry to the log window
 * @param str
 * The log to add
 * @param log_win
 * The log window
 * @param cur_line
 * The current line the log is on.
 * If the log window will overflow, it will be cleared first
 */
void addLog(const char *str, WINDOW *log_win, int *cur_line);

#endif //MORSE_UI_MORSE_FUNCTIONS_H
