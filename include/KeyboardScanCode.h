#ifndef KEAYBOARD_SCAN_CODE
#define KEAYBOARD_SCAN_CODE

#include "stdint.h"

const char ScanCodeTable[] = {
    0, 0, '1', '2',
    '3', '4', '5', '6',
    '7', '8', '9', '0',
    '-', '=', 0, 0,
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i',
    'o', 'p', '[', ']',
    0, 0, 'a', 's',
    'd', 'f', 'g', 'h',
    'j', 'k', 'l', ';',
    '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',',
    '.', '/', 0, '*',
    0, ' '
};

/**
 * @brief callback function for keyboard driver
 * 
 */
using keyboard_cb = void(*)(u8 scanCode, u8 chr);

/**
 * @brief Active slot for keayboard callback
 * 
 */
extern keyboard_cb MainKeyboardHandler;


/**
 * @brief Default keyboard driver
 * 
 * @param scanCode scancode from io keyboard memory
 * @param chr parsed char data from scancode
 */
void KeyboardHandler(u8 scanCode, u8 chr);

#endif