#include "Validation.h"

Validation & Validation::getInstance()
{
	static Validation inst;
	return inst;
}
Validation::Validation() :system("Admin", 45)
{

}
const char * Validation::addUsersCommand(const char * actorName, const char * action, const char * sbjName, size_t age)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;

	int indexSbj = checkNameExist(sbjName);
	if (!(indexSbj == NOSUCH_USER))
		return ALREADY_EXIST;
	
	if (age < 18 || age>99)
		return INCORRECT_AGE;

	if (!system.addUser(action, sbjName, age, indexActor))
		return NO_PERMISSION_ADD_USER;
	else
		return SUCCSSES_ADD_USER;
}

const char * Validation::removeUsersCommand(const char * actorName, const char * sbjName)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;

	int indexSbj = checkNameExist(sbjName);
	if (indexSbj == NOSUCH_USER)
		return NOT_FOUND_SUBJECT;

	Result result = system.removeUser(indexActor, indexSbj);
	switch (result)
	{
	case REMOVE_ADMIN:
		return ADMNISTRATION_REMOVE;
	case NO_PERMISSION:
		return NO_PERMISSION_REMOVE_USER;
	default:
		return SUCCSSES_REMOVE_USER;
	}
}

void Validation::infoCommand(std::ostream & os) const
{
	if (!os)
		return;
	size_t size = system.getCurrUsers();
	os << "There are " << size << " users:\n";
	os << system.getName(0) << "- Administrator, " << system.getCntPosts(0)<<" posts." << "\n";
	for (size_t i = 1; i < size; ++i)
	{
		if (system.isModerator(i))
			os << system.getName(i) << "- Moderator, " << system.getCntPosts(i) << " posts." << "\n";
		else
			os << system.getName(i) << "- Simple Users, " << system.getCntPosts(i) << " posts." << "\n";
	}
	size_t cntBlocked = cntBlockUsers(size);
	if (!cntBlocked)
		os << "There are not any blocked users.\n";
	else
	{
		os << "There are " << cntBlocked << " blocked users:\n";
		for (size_t i = 1; i < size; ++i)
		{
			if (system.getStatus(i))
				os <<"BLOCKED "<<i<<":"<< system.getName(i) << "," << system.getAge(i)<<"\n";
		}
	}

	size_t indexOldest=0, indexYoungest=0;
	findOldYoungUser(&indexOldest, &indexYoungest,size);
	os << "Oldest users:" << system.getName(indexOldest) << "," << system.getAge(indexOldest) << "\n";
	os << "Youngest users:" << system.getName(indexYoungest) << "," << system.getAge(indexYoungest) << "\n";

}

const char * Validation::blockUnblockCommand(const char * actorName, const char * sbjName, bool block_unblock)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor==NOSUCH_USER)
		return NOT_FOUND_ACTOR;

	int indexSbj = checkNameExist(sbjName);
	if (indexSbj == NOSUCH_USER)
		return NOT_FOUND_SUBJECT;

	Result result = system.blockUnblockUser(indexActor, indexSbj, block_unblock);
	switch (result)
	{
	case REMOVE_ADMIN:
		return ADMINISTRATION_BLOCK;
	case NO_PERMISSION:
		return NO_PERMISSION_BLOCK_UNBLOCK;
	case USER_BLOCKED:
		return BLOCKED_USER;
	default:
		return SUCCSSES_BLOCK_UNBLOCK;
	}

}

const char * Validation::addPostCommand(const char * actorName, const char * type, const char * content, const char * des)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;
	Result result = system.addPost(indexActor, type, content, des);
	switch (result)
	{
	case UNKNOWN_POST:
		return "No such type of posts!\\n";//не би трябвало да влезнем тук
	case INVALID_ARGUMENT:
		return INVALID_ARGUMENT_PASS;
		break;
	case USER_BLOCKED:
		return BLOCKED_USER;
		break;
	default://succsess
		std::cout << Post::getCnt() - 1;
		return " post was created!\n";
	}
}

const char * Validation::removePostCommand(const char * actorName, size_t ID)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;
	bool stat = system.getStatus(indexActor);
	if (stat)
		return BLOCKED_USER;
	size_t ownerOfPosts = 0;
	int result = searchPost(&ID, &ownerOfPosts);
	if (result == REMOVE_ADMIN && indexActor)//само админа може да си изтрие публикациите
		return ADMNISTRATION_REMOVE;
	else if (result == NOSUCH_POST)
		return INVALID_POST;
	if (indexActor == ownerOfPosts)//тоест опитва се да изтрие свой пост,ок
	{
		system.removePost(indexActor, ID);
		return SUCCSSES_REMOVE_OWN_POST;
	}
	if (system.isModerator(indexActor))
	{
		system.removePost(ownerOfPosts, ID);
		return SUCCSSES_REMOVE_OTHER_POST;
	}
	else
		return NO_PERMISSION_REMOVE_POST;
}

const char * Validation::makeHTMLCommand(const char * actorName, size_t ID)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;
	size_t postOwner = 0;
	int result = searchPost(&ID, &postOwner);
	if (result == NOSUCH_POST)
		return INVALID_POST;
	if (!system.makeHtmlFile(postOwner, ID))
		return FILE_PROBLE;
	return SUCCSSES_HTML;
}

const char * Validation::makeHTMLallCommand(const char * actorName, const char * sbjName)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;

	int indexSbj = checkNameExist(sbjName);
	if (indexSbj == NOSUCH_USER)
		return NOT_FOUND_SUBJECT;

	Result result = system.makeAllFtmlFile(indexSbj);
	switch (result)
	{
	case PROBLEN_FILE:
		return FILE_PROBLE;
	case NO_POST:
		return NO_POUST_USERS;
	default:
		return SUCCSSES_HTML_ALL;
	}

}

const char * Validation::renameCommand(const char * actorName, const char * newName)
{
	int indexActor = checkNameExist(actorName);
	if (indexActor == NOSUCH_USER)
		return NOT_FOUND_ACTOR;

	int indexNewName = checkNameExist(newName);
	if (!(indexNewName == NOSUCH_USER))
		return ALREADY_EXIST;

	system.rename(indexActor, newName);
	return SUCCSSES_RENAME;
}


int Validation::searchPost(size_t* ID, size_t * PostsOf)const
{
	size_t size = system.getCurrUsers();
	for (size_t i = 0; i < size; ++i)
	{
		size_t cntPosts = system.getCntPosts(i);
		for (size_t j = 0; j < cntPosts; ++j)
		{
			if (system.getUserPostsID(i, j) == *ID)
			{
				if (i == 0)
				{
					*ID = j;
					*PostsOf = i;
					return REMOVE_ADMIN;
				}
				else
				{
					*ID = j;//променяме системного ID
					       //,тъй като подаденото не отговаря на реда на поста на съответния потребител
					*PostsOf = checkNameExist(system.getName(i));//и взимаме индекса на съответния потребител
					return SUCCSESS;
				}
			}
			if (system.getUserPostsID(i, j) > *ID)//значи постът е изтрит и няма смисъл да търсим нататък
				return NOSUCH_POST;
		}
	}
	return  NOSUCH_POST;
}


int Validation::checkNameExist(const char * name)const
{
	size_t size = system.getCurrUsers();

	for (size_t i = 0; i <size; ++i)
	{
		if (!strcmp(system.getName(i), name))
			return i;
	}
	return NOSUCH_USER;

}

void Validation::findOldYoungUser(size_t * oldest, size_t * youngest,size_t size)const
{
	size_t currOldest = system.getAge(0);
	size_t currYoungest = currOldest;

	for (size_t i = 1; i < size; ++i)
	{
		size_t currAge = system.getAge(i);
		if (currAge > currOldest)
		{
			*oldest = i;
			currOldest = currAge;
		}
		else if (currAge < currYoungest)
		{
			*youngest = i;
			currYoungest = currAge;
		}
	}
}

size_t Validation::cntBlockUsers(size_t size)const
{
	size_t cnt = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (system.getStatus(i))
			++cnt;
	}
	return cnt;
}
