#include "Moderator.h"


Moderator::Moderator(const char * name, size_t age) :Users(name, age)
{

}
Users * Moderator::clone() const
{
	return new Moderator(*this);
}

bool Moderator::canBlockUnblock() const
{

	return true;
}


bool Moderator::canAdd() const
{
	return false;
}


bool Moderator::canRemove() const
{
	return false;
}
