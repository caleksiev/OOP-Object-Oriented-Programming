#ifndef VID_HEADER_INCLUDED
#define VID_HEADER_INCLUDED
#include"Tag.h"
class Video :public Tag
{
public:
	Video(const char*des, const char*text);

public:
	virtual const char*whatAmI()const;
	virtual Tag*clone()const;
	bool virtual writeOnHile(std::ostream&os)const;

};
#endif