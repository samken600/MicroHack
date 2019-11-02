/*
 * main.h
 *
 *  Created on: 27 Oct 2019
 *      Author: Richard Carter
 */

#ifndef ASCII_GAME_TEMPLATE_H_
#define ASCII_GAME_TEMPLATE_H_

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// Prototypes
COORD GetCoord(void);
void SetCoord(COORD coords);

// Global Variables
HANDLE hStdOut;

#endif /* ASCII_GAME_TEMPLATE_H_ */
