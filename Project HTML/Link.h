#ifndef LINK_HEADER_INCLUDED
#define LINK_HEADER_INCLUDED
#include"Tag.h"
class Link :public Tag
{
public:
	Link(const char*des, const char*text, const char*linkDes);
	Link(const Link&other);
	Link&operator=(const Link&other);
	~Link();

public:
	virtual const char*whatAmI()const;
	virtual Tag*clone()const;
	bool virtual writeOnHile(std::ostream&os)const;

private:
	void clean();
	void copyFrom(const Link&other);
private:
	void setLinkDes(const char*linkDes);
private:
	char*linkDes;
};
#endif