#include "Users.h"

Users::Users(const char * name, size_t age):cntCurrPosts(0),cntRealPosts(0),posts(nullptr),name(nullptr)
{
	if (!name)
		throw std::invalid_argument("NULL PTR PASS TO USER");
	setName(name);
	setAge(age);
	setIsBlock(false);
}
//инициализирам всички стойности с дефоултните в ин.списък
// за да може в случай на неуспешно създаване на обекта,той да има невалидни данни
Users::Users(const Users & other):posts(nullptr),name(nullptr)
, cntCurrPosts(0), cntRealPosts(0),age(0),isBlocked(0)
{
	copyFrom(other);
}

Users & Users::operator=(const Users & other)
{
	if (this != &other)
	{
		//едва след като е успешно копирането ще унищожим данните за this-> обекта
		Post**temp = posts;
		size_t oldCurrSize = cntCurrPosts;
		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&())
		{
			posts = temp;
			cntCurrPosts = oldCurrSize;
			throw;
		}
		clearTemp(temp);
	}
	return*this;
}

Users::~Users()
{
	clearAll();
}

Result Users::addPost(const char * type, const char * content, const char * description)
{
	if (!type || !content )//des може и да е 0,защото е по-подразбиране
		return INVALID_ARGUMENT;
	if (isBlocked)
		return USER_BLOCKED;
	if (cntCurrPosts == cntRealPosts)
	{
		size_t newCap = cntCurrPosts ? 2 * cntCurrPosts : 2;
		resize(newCap);
	}

	posts[cntCurrPosts] = PostFactory::createPost(type, content, description);
	if (!posts[cntCurrPosts])
		return UNKNOWN_POST;
	++cntCurrPosts;

	return SUCCSESS;
}

void Users::removePost(size_t index)
{
	if (!cntCurrPosts)
		throw std::length_error("There are no more posts");
	if (index >= cntCurrPosts)
		throw std::invalid_argument("INVALID ID FOR REMOVING POSTS");

	for (size_t i = index; i < cntCurrPosts - 1; ++i)//приемам,че тук няма какво да се обърка :(
		std::swap(posts[i], posts[i + 1]);
	
	--cntCurrPosts;
	if (cntCurrPosts * 2 <= cntRealPosts)
		resize(cntRealPosts/2);
}

bool Users::makeHtmlFile(size_t index)
{
	if(index>=cntCurrPosts)
		throw std::invalid_argument("INVALID ID FOR HTML POSTS");

	std::fstream f;
	f.open("f.html", std::ios::out);
	if (!f.is_open())
		return false;
	f << "<!DOCTYPE html>" << "\n" << "<html>" << "\n" << "<body>" << "\n";
	if (posts[index]->makeHTMLfile(f)){
		f << "\n" << "</body>" << "\n" << "</html>";
		f.close();
		return true;
	}
	remove("f.html");
	f.close();
	return false;
}

Result Users::makeHtmlAllFile()
{
	if (!cntCurrPosts)
		return NO_POST;
	std::fstream f;
	f.open("f.html", std::ios::out);
	if (!f.is_open())
		return PROBLEN_FILE;
	f << "<!DOCTYPE html>" << "\n" << "<html>" << "\n" << "<body>" << "\n";
	for (size_t i = 0; i < cntCurrPosts && f.good(); ++i)
	{
		f << "<p>"<<i << " post:" << "</p>";
		if (!posts[i]->makeHTMLfile(f))
		{
			remove("f.html");
			f.close();
			return PROBLEN_FILE;
		}
		f << "\n";
	}
	f << "\n" << "</body>" << "\n" << "</html>";
	f.close();
	return SUCCSESS;
}


const char * Users::getName() const
{
	return name;
}

bool Users::getStatus() const
{
	return isBlocked;
}

size_t Users::getAge() const
{
	return age;
}

size_t Users::getCntPosts() const
{
	return cntCurrPosts;
}

size_t Users::getID(size_t index) const
{
	if (index >= cntCurrPosts)
		throw std::invalid_argument("INVALID INDEX OF GETPOST");
	return posts[index]->getID();
}

void Users::resize(size_t newCap)
{
	Post**temp = posts;

	try
	{
		posts = new Post*[newCap];
	}
	catch (const std::bad_alloc())
	{
		posts = temp;
		throw;
	}
	allToNull(newCap);
	try
	{
		for (size_t i = 0; i < cntCurrPosts; ++i)
			posts[i] = temp[i]->clone();
	}
	catch (const std::bad_alloc&())
	{
		clearPosts();
		posts = temp;
		throw;
	}
	clearTemp(temp);
	setRealPosts(newCap);
}

void Users::copyFrom(const Users & other)
{
	posts = new Post*[other.cntRealPosts];
	setCurrPosts(other.cntCurrPosts);
	allToNull(other.cntRealPosts);
	try
	{
		for (size_t i = 0; i < other.cntCurrPosts; ++i)
			posts[i] = other.posts[i]->clone();

		setName(other.name);
	}
	catch (const std::bad_alloc&())
	{
		setCurrPosts(0);
		clearPosts();
		throw;
	}
	setRealPosts(other.cntRealPosts);
	setAge(other.age);
	setIsBlock(other.isBlocked);
}

void Users::clearAll()
{
	clearPosts();
	clearName();
}

void Users::clearPosts()
{
	for (size_t i = 0; i < cntRealPosts; ++i)
		delete posts[i];
	delete[] posts;
	posts = nullptr;
}

void Users::clearName()
{
	delete[]name;
	name = nullptr;
}

void Users::clearTemp(Post **& temp)
{
	for (size_t i = 0; i < cntRealPosts; ++i)
		delete temp[i];
	delete[] temp;
}

void Users::allToNull(size_t size)
{
	for (size_t i = 0; i < size; ++i)
		posts[i] = nullptr;
}

void Users::setName(const char * name)
{
	delete[] this->name;
	this->name = new char[strlen(name )+1];
	strcpy(this->name, name);
}

void Users::setAge(const size_t age)
{
	this->age = age;
}

void Users::setIsBlock(bool isBlock)
{
	this->isBlocked = isBlock;
}

void Users::setCurrPosts(size_t cnt)
{
	this->cntCurrPosts = cnt;
}

void Users::setRealPosts(size_t cnt)
{
	this->cntRealPosts = cnt;
}
