#ifndef _USERFACT_HEADER_INCLUDED_
#define _USERFACT_HEADER_INCLUDED_
#include"Simple-User.h"
#include"Moderator.h"
#include"Admin.h"
class User_Factory
{
public:
	static Users* createUser(const char*type, const char*name, size_t age)
	{
		if (!strcmp(type, "add_user"))
			return new Simple_Users(name, age);
		else if (!strcmp(type, "add_moderator"))
			return new Moderator(name, age);
		else if (!strcmp(type, "add_admin"))//тази опция е ненужна засега,но в бъдеше може и да потрябва
			return new Admin(name, age);
		else
			return NULL;
	}
};
#endif
