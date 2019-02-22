#ifndef _MENU_HEADER_INCLUDED_
#define _MENU_HEADER_INCLUDED_
#include"Validation.h"
const size_t MAXLEN_NAME = 20;
const size_t MAXLEN_COMMAND = 15;
const size_t MAXLEN_POST = 10;
const size_t MAXLEN_CONTENT = 120;

void skipSpaces();

void signalWrong();

void Menu();

#endif

