#ifndef _SUSERS_HEADER
#define _SUSERS_HEADER
#include"Users.h"
class Simple_Users :public Users
{
public:
	Simple_Users(const char*name, size_t age);
	virtual bool canBlockUnblock()const;
	virtual bool canAdd()const;
	virtual Users*clone()const;
	virtual bool canRemove()const;

};
#endif
