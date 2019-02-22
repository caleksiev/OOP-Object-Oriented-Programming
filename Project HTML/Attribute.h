#ifndef ATRIB_HEADER_INCLUDED
#define ATRIB_HEADER_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include <exception>
#include<algorithm>
#include<fstream>
const unsigned int MAX_NAME = 10;
class Attribute
{
public:
	Attribute(const char*name, const char*value);
	Attribute(const Attribute&other);
	Attribute& operator=(const Attribute&other);
	~Attribute();

	Attribute*clone()const;
	const char*getName() const { return name; }
	const char*getValue()const { return value; }
private:
	void copyFrom(const Attribute&other);
	void clean();
	void setName(const char*name);
	void setValue(const char*value);
private:
	char name[MAX_NAME];
	char*value;
};
#endif
