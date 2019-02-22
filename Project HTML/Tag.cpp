#include "Tag.h"

Tag::Tag(const char * des, const char*cont) :description(nullptr), content(nullptr),attribute(nullptr),size(0),cap(0)
{
	if (!des || !cont)
		throw std::invalid_argument("NULL PTR PASS TO Tag CTOR");
	try
	{
		setDescription(des);
		setContent(cont);
	}
	catch (const std::bad_alloc&()){
		clean(description,content,attribute,cap);
		throw;
	}
}

Tag::Tag(const Tag & other) :description(nullptr), content(nullptr), attribute(0), size(0), cap(0)
{
	copyFrom(other);
}

Tag & Tag::operator=(const Tag & other)
{
	if (this != &other)
	{
		char*oldDes = description;
		char*oldCont = content;
		Attribute**oldAtt = attribute;
		size_t oldCap = cap;
		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&())
		{
			description = oldDes;
			content = oldCont;
			attribute = oldAtt;
			throw;
		}
		clean(oldDes, oldCont, oldAtt,oldCap);
	}
	return *this;
}

Tag::~Tag()
{
	clean(description,content,attribute,cap);
}

void Tag::addAtr(const char * name, const char * value)
{
	if (!name || !value)
		throw std::invalid_argument("NULL PTR PASS TO ATTRIBUT!\n");
	if (size == cap)
	{
		size_t newCap = size ? 2 * size : 2;
		resize(newCap);
	}
		attribute[size++] = new Attribute(name, value);
}

void Tag::setDescription(const char * des)
{
	description = new char[strlen(des) + 1];
	strcpy(description, des);
}

void Tag::setContent(const char * cont)
{
	content = new char[strlen(cont) + 1];
	strcpy(content, cont);
}

void Tag::setAttribute(size_t size)
{
	if (!size)
		attribute = nullptr;
	else
		attribute = new Attribute*[size];
}

void Tag::setSize(size_t size)
{
	this->size = size;
}

void Tag::setCap(size_t cap)
{
	this->cap = cap;
}

void Tag::clean(char*&description, char*&content, Attribute**&attribute,size_t cap)
{
	delete[]description;
	delete[]content;
	content = nullptr;
	description = nullptr;
	cleanAtt(attribute, cap);
}

void Tag::cleanAtt(Attribute **& attribute,size_t size)
{
	for (size_t i = 0; i < size; ++i)
		delete attribute[i];
	delete[]attribute;
	attribute = nullptr;
}

void Tag::copyFrom(const Tag & other)
{
	try
	{
		setDescription(other.description);
		setContent(other.content);
		setAttribute(other.cap);
		allToNull(other.cap);

		
		for (size_t i = 0; i < other.size; ++i)
			attribute[i] = other.attribute[i]->clone();
	}
	catch (const std::bad_alloc&()){
		clean(description,content,attribute,other.size);
		throw;
	}
	setSize(other.size);
	setCap(other.cap);
}

void Tag::resize(size_t newCap)
{
	Attribute**temp = attribute;
	setAttribute(newCap);
	allToNull(newCap);
	size_t min = std::min(newCap, size);

	try
	{
		for (size_t i = 0; i < min; ++i)
			attribute[i] = temp[i]->clone();
	}
	catch (const std::bad_alloc&)
	{
		cleanAtt(attribute, min);
		attribute = temp;
		throw;
	}
	cleanAtt(temp,cap);
	setCap(newCap);

}

void Tag::allToNull(size_t cap)
{
	for (size_t i = 0; i < cap; ++i)
		attribute[i]= nullptr;
}
