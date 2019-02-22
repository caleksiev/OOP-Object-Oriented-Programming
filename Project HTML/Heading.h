#ifndef HED_HEADER_INCLUDED
#define HED_HEADER_INCLUDED
#include"Tag.h"
class Heading :public Tag
{
public:
	Heading(const char*des,const char*text, unsigned short size);

private:
	virtual const char*whatAmI()const;
	virtual Tag*clone()const;
	bool virtual writeOnHile(std::ostream&os)const;

private:
	void setSize(unsigned short size);
private:
	unsigned short sizeH;//размера на заглавието-число-[1-6]
};
#endif
