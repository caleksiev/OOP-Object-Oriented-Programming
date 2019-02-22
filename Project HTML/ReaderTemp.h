#ifndef RTEMP_HEADER_INCLUDED
#define RTEMP_HEADER_INCLUDED
#include<fstream>
bool isLetter(char s);

bool isSpecial(char s);

void skipSpace(std::fstream&f);

void skipUnletter(char*&ptrCnt);

void copyText(char*&ptrCnt, char*store);

void copyText1(char*&ptrCnt, char*store);

void copyText2(char*&ptrCnt, char*store);

void copyTextLink(char*&ptrCnt, char*store);

bool isAtribb(const char * text);

bool isMetaData(const char * text);
#endif
