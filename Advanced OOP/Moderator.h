#ifndef _MOD_HEADER_
#define _MOD_HEADRE_
#include"Users.h"
class Moderator:public Users
{
public:
	Moderator(const char*name, size_t age);

	virtual bool canBlockUnblock()const ;
	virtual bool canAdd()const;
	virtual Users*clone()const ;
	virtual bool canRemove()const ;
};
#endif
