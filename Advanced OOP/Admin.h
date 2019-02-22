#ifndef _ADMIN_HEADER_INCLUDED
#define _ADMIN_HEADER_INCLUDED
#include"Users.h"
class Admin :public Users
{
public:
	Admin(const char*name, size_t age);

	virtual bool canBlockUnblock()const;
	virtual bool canAdd()const;
	virtual Users*clone()const;
	virtual bool canRemove()const ;

};
#endif
