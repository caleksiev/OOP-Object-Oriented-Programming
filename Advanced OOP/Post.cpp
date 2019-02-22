#include "Post.h"

size_t Post::cnt = 0;

Post::Post(const char * content):content(nullptr)
{
	if (!content)
		throw std::invalid_argument("NULL PTR PASS TO POST");
	setContent(content);
	setID(cnt++);
}

Post::Post(const Post & other):content(nullptr)
{
	copyFrom(other);
}

Post & Post::operator=(const Post & other)
{
	if (this != &other)
	{
		char*oldContent = content;
		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&())
		{
			content = oldContent;
			throw;
		}
		delete[]oldContent;
	}
	return*this;
}

Post::~Post()
{
	clean();
}

size_t Post:: getID()const {
	return ID; 
}
size_t Post::getCnt()
{
	return cnt;
}

void Post::setContent(const char * content)
{

	this->content = new char[strlen(content) + 1];
	strcpy(this->content, content);

}

void Post::setID(size_t ID)
{
	this->ID = ID;
}

void Post::copyFrom(const Post & other)
{
	setContent(other.content);
	setID(other.ID);
}

void Post::clean()
{
	delete[]content;
	ID = 0;
	content = nullptr;
}

