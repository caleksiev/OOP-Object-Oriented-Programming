#include "Simple-User.h"

Simple_Users::Simple_Users(const char * name, size_t age):Users(name,age)
{

}
bool Simple_Users::canBlockUnblock( )const
{
	return false;
}



bool Simple_Users::canAdd() const
{
	return false;
}

Users * Simple_Users::clone() const
{
	return new  Simple_Users(*this);
}

bool Simple_Users::canRemove() const
{
	return false;
}





