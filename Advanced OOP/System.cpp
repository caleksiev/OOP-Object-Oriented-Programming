#include "System.h"

//първия в масива с потребители е админа!!!
System::System(const char * adminName, size_t adminAge):cntCurrUsers(0),cntRealUsers(2),users(nullptr)
{
	if (!adminName)
		throw std::invalid_argument("NULL ptr pass to ADMIN");
	users = new Users*[cntRealUsers];
	allToNullPtr(cntRealUsers);
	try
	{
		users[cntCurrUsers++] = new Admin(adminName, adminAge);
	}
	catch (const std::bad_alloc&())
	{
		delete[]users;
		throw ;
	}
}

System::~System()
{
	clearUsers(users);
}

bool System::addUser(const char * type, const char * name, size_t age, size_t indexWho)
{
	if (!type || !name || indexWho >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO ADD USERS FUNCTION!\n");
	if (users[indexWho]->canAdd())
	{
		if (cntCurrUsers == cntRealUsers)
			resize(cntCurrUsers * 2);

		users[cntCurrUsers] = User_Factory::createUser(type, name, age);

		if (!users[cntCurrUsers])//не би трябвало да влезнем тук,но класа няма как да го знае
			return false;
		++cntCurrUsers;
		return true;
	}
	else
		return false;
}

Result System::removeUser( size_t remover,size_t removed)
{
	if(remover>=cntCurrUsers || removed>=cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO REMOVE USERS FUNCTION!\n");
	if (!cntCurrUsers)
		throw std::length_error("There are no more users");
	if (!removed)
		return REMOVE_ADMIN;
	if (users[remover]->canRemove())
	{
		for (size_t i = removed; i < cntCurrUsers - 1; ++i)
			std::swap(users[i], users[i + 1]);

		--cntCurrUsers;

		if (cntCurrUsers * 2 <= cntRealUsers)
			resize(cntRealUsers / 2);
		return SUCCSESS;
	}
	else
		return NO_PERMISSION;
	;
}

Result System::blockUnblockUser(size_t blocker, size_t blocked,bool flag)
{
	if (blocker >= cntCurrUsers || blocked >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO BLOCK FUNCTION!\n");
	if (!blocked)
		return REMOVE_ADMIN;
	if (users[blocker]->canBlockUnblock())
	{
		if (users[blocker]->getStatus())
			return USER_BLOCKED;
		if (flag)
			users[blocked]->isBlocked = true;
		else
			users[blocked]->isBlocked = false;
		return SUCCSESS;
	}
	else
		return NO_PERMISSION;
}
const char * System::getName(size_t index) const
{
	if (index>=cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO GETNAME FUNCTION!\n");
	return users[index]->getName();
}

size_t System::getCurrUsers() const
{
	return cntCurrUsers;
}

size_t System::getAge(size_t index) const
{
	if(index >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO GETAGE FUNCTION!\n");
	return users[index]->getAge();
}

bool System::getStatus(size_t index) const
{
	if (index >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO GETSTATUS FUNCTION!\n");
	return users[index]->getStatus();
}

size_t System::getCntPosts(size_t index) const
{
	if (index >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO GETCNTPOST FUNCTION!\n");
	return users[index]->getCntPosts();
}

size_t System::getUserPostsID(size_t indexU, size_t indexP) const
{
	if (indexU >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO GETIDPOST FUNCTION!\n");
	return users[indexU]->getID(indexP);
}

void System::rename(size_t index,const char*newName)
{
	if (index >= cntCurrUsers || !newName)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO RENAME FUNCTION!\n");
	users[index]->setName(newName);
}

Result System::addPost(size_t poster, const char * type, const char * content, const char * des)
{
	if (poster >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO ADDPOST FUNCTION!\n");
	return users[poster]->addPost(type, content, des);
}

void System::removePost(size_t remover, size_t postID)
{
	if (remover >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO REMOVEPOST FUNCTION!\n");
	return users[remover]->removePost(postID);
}

bool System::makeHtmlFile(size_t receiver, size_t postID)
{
	if (receiver >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO HTML FUNCTION!\n");
	return users[receiver]->makeHtmlFile(postID);
}

Result System::makeAllFtmlFile(size_t receiver)
{
	if (receiver >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO HTML FUNCTION!\n");
	return users[receiver]->makeHtmlAllFile();
}

bool System::isModerator(size_t index)const
{
	if (index >= cntCurrUsers)
		throw std::invalid_argument("INVALID ARGIMENTS PASS TO ISMOD FUNCTION!\n");
	if (users[index]->canBlockUnblock())
		return true;
	return false;
}

void System::allToNullPtr(size_t size)
{
	for (size_t i = 0; i < size; ++i)
		users[i] = nullptr;
}

void System::clearUsers(Users **& users)
{
	for (size_t i = 0; i < cntRealUsers; ++i)//до реалния размер защото може да има неизтрити потребители извън
		delete users[i];                      //текущия размер(сигурни сме,че след текущия размер другите сочат към 0)
	delete[]users;
	users = nullptr;
}

void System::resize(size_t newCap)
{
	Users**temp = users;
	try
	{
		users = new Users*[newCap];
	}
	catch (const std::bad_alloc())
	{
		users = temp;
		throw;
	}
	allToNullPtr(newCap);
	try
	{
		for (size_t i = 0; i < cntCurrUsers; ++i)
			users[i]=temp[i]->clone();
	}
	catch (const std::bad_alloc&())
	{
		clearUsers(users);
		users = temp;
		throw;
	}
	clearUsers(temp);
	cntRealUsers = newCap;
}
