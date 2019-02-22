#ifndef MENU_HEADER_INCLUDED
#define MENU_HEADER_INCLUDED
#include"Reader.h"
const size_t MAX_FILE_LEN = 240;
const size_t MAX_COMM_LEN = 20;
const size_t MAX_CONTENT = 500;

void skipRest();

void skipSpaces();

void Menu();

void Menu1(bool* exit, Reader& r);

void attribMenu(const char*type, size_t index, Reader&r);

#endif
