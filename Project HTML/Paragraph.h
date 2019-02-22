#ifndef PAR_HEADER_INCLUDED
#define PAR_HEADER_INCLUDED
#include"Tag.h"
class Paragraph:public Tag
{
public:
	Paragraph(const char*des, const char*text);

public:
	virtual const char*whatAmI()const;
	virtual Tag*clone()const;
	bool virtual writeOnHile(std::ostream&os)const;
};
#endif
