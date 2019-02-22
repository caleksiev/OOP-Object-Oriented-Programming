#include"ReaderTemp.h"

bool isLetter(char s)
{
	return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

bool isSpecial(char s)
{
	return (s == '/') || (s == '.') || (s == '-') || (s == ':')
		|| (s >= '0' && s <= '9') || (s == '\\');
}
void skipSpace(std::fstream&f)
{
	char s = f.get();
	while (s == ' ' || s == '\n')
		s = f.get();
	f.unget();
}

void skipUnletter(char*&ptrCnt)
{
	while (*ptrCnt && !isLetter(*ptrCnt))
		++ptrCnt;
}
void copyText(char*&ptrCnt, char*store)
{
	size_t i = 0;
	for (; *ptrCnt && isLetter(*ptrCnt); ++i, ++ptrCnt)
		store[i] = *ptrCnt;
	store[i] = '\0';
}
void copyText1(char*&ptrCnt, char*store)
{
	size_t i = 0;
	for (; *ptrCnt; ++i, ++ptrCnt)
		store[i] = *ptrCnt;
	store[i] = '\0';
}
void copyTextLink(char*&ptrCnt, char*store)
{
	size_t i = 0;
	for (; *ptrCnt && (isLetter(*ptrCnt) || isSpecial(*ptrCnt)); ++i, ++ptrCnt)
		store[i] = *ptrCnt;
	store[i] = '\0';
}
void copyText2(char*&ptrCnt, char*store)
{
	size_t i = 0;
	for (; *ptrCnt && *ptrCnt != '"'; ++i, ++ptrCnt)
		store[i] = *ptrCnt;
	store[i] = '\0';
}


bool isAtribb(const char * text)
{
	if (!strcmp(text, "alt") || !strcmp(text, "width")
		|| !strcmp(text, "height") || !strcmp(text, "title") || !strcmp(text, "align"))
		return true;
	else
		return false;
}
bool isMetaData(const char * text)
{
	if (!strcmp(text, "<!DOCTYPE html") || !strcmp(text, "<html")
		|| !strcmp(text, "<head") || !strcmp(text, "<body") || !strcmp(text, "</head")
		|| !strcmp(text, "</html") || !strcmp(text, "</body"))
		return true;
	else
		return false;
}