#include "Admin.h"

Admin::Admin(const char * name, size_t age) :Users(name, age)
{
}

Users * Admin::clone() const
{
	return new Admin(*this);
}

bool Admin::canBlockUnblock() const
{
	return true;
}


bool Admin::canAdd() const
{
	return true;
}


bool Admin::canRemove() const
{
	return true;
}
