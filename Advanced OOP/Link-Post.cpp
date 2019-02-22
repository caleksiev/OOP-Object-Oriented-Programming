#include "Link-Post.h"

Link_Post::Link_Post(const char * content, const char * description):Post(content),description(nullptr)
{
	if (!description)
	{
		Post::clean();
		throw std::invalid_argument("NULL PTR PASS TO POST");
	}
	try
	{
		setDes(description);
	}
	catch (const std::bad_alloc&)
	{
		Post::clean();
		throw;
	}
}

Link_Post::Link_Post(const Link_Post & other):Post(other),description(nullptr)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc&)
	{
		Post::clean();
		throw;
	}
}

Link_Post & Link_Post::operator=(const Link_Post & other)
{
	if (this != &other)
	{
		char*oldDes = description;
		Post::operator=(other);
		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&())
		{
			Post::clean();
			description = oldDes;
			throw;
		}
		delete[]oldDes;
	}
	return *this;
}

Link_Post::~Link_Post()
{
	clean();
}

bool Link_Post::makeHTMLfile(std::ostream &f)const
{
	if (!f.good())
		return false;


	f <<"<p>"<< "<a href=" <<"\""<< content <<"\"" << ">"
		<< description<<"</a>" << "</p>";

	if (f.good())
		return true;
	return false;
}

Post * Link_Post::clone()const
{
	return new Link_Post(*this);
}

void Link_Post::setDes(const char * des)
{
	description = new char[strlen(des) + 1];
	strcpy(description, des);
}

void Link_Post::copyFrom(const Link_Post & other)
{
	setDes(other.description);
}

void Link_Post::clean()
{
	delete[]description;
	description = nullptr;
}
