#ifndef IMG_HEADER_INCLUDED
#define IMG_HEADER_INCLUDED
#include"Tag.h"
class Image :public Tag
{
public:
	Image(const char*des, const char*text);
public:
	virtual const char*whatAmI()const;
	virtual Tag*clone()const;
	bool virtual writeOnHile(std::ostream&os)const;

};
#endif
