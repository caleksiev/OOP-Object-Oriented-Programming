#include "System.h"

System::System(const char * fileName):filename(nullptr),tags(nullptr),size(0),cap(0)
{
	if (!fileName)
		throw std::invalid_argument("NULL PTR PASS TO SYSTEM CTOR!\n");
	setFileName(fileName);
}

System::System(const System & other):filename(nullptr), tags(nullptr)
{
	copyFrom(other);
}

System & System::operator=(const System & other)
{
	if (this != &other)
	{
		Tag**temp = tags;
		size_t oldCap = cap;

		try
		{
			copyFrom(other);
		}
		catch (const std::bad_alloc&())
		{
			tags = temp;
			throw;
		}
		clean(temp,oldCap);

	}
	return *this;
}

System::~System()
{
	clean(tags,cap);
}

void System::addTags(const char * command, const char * des, const char * content
	,const char*linkDes,unsigned short n)
{
	if (!command || !des || !content)
		throw std::invalid_argument("NULL PTR PASS TO ADD TAG FUNC!\n");
	if (size == cap)
	{
		size_t newCap = size ? size * 2 : 2;
		resize(newCap);
	}
	try
	{
		tags[size++] = TagFactory::createTag(command, des, content, linkDes, n);
	}
	catch (const std::bad_alloc&())
	{
		--size;
		throw;
	}
}

void System::removeTag(size_t index)
{
	if (index >= size)
		throw std::out_of_range("INVALID INDEX FOR REMOVEING TAG!\n");
	if(!size)
		throw std::out_of_range("THERE IS NO MORE TAGS LEFT FOR REMOVING !\n");
	if (index == size - 1)
		--size;
	else
	{
		for (size_t i = index; i < size - 1; ++i)//приемаме,че няма какво да се обърка
			std::swap(tags[i], tags[i + 1]);
		--size;
	}
	if (size * 2 <= cap)
		resize(cap / 2);
}

void System::moveTo(size_t index, size_t where)
{
	if (index >= size || where>=size)
		throw std::out_of_range("INVALID INDEX FOR MOVING TAG!\n");
	Tag*temp = tags[index];
	if (index == where)
		return;
	size_t i = index;
	try
	{
		if (index > where)
		{
			for (; i > where; --i)
				tags[i] = tags[i - 1];
		}
		else
		{
			for ( ; i < where; ++i)
				tags[i] = tags[i + 1];
		}
	}
	catch (const std::bad_alloc&())
	{
		tags[i] = temp;//редът ще се обърка на поне информацията ще се запази
		throw;
	}
	
	tags[where] = temp;
}

void System::addAtt(size_t tag_index, const char * name, const char * value)
{
	if (tag_index >= size || !name || !value)
		throw std::invalid_argument("INCORRECT DATA FOR ADDING ATTRIBUTE!\n");
	tags[tag_index]->addAtr(name, value);
}

bool System::saveData() const
{
	std::fstream f;
	f.open(filename, std::ios::out);
	if (!f.is_open())
		return false;
	f << "<!DOCTYPE html>\n" << "<html>\n" << "<head> </head>\n" << "<body>\n";
		for (size_t i = 0; i < size && f.good(); ++i)
		{
			if (!tags[i]->writeOnHile(f))
				return false;
		}
		f << "</body>\n" << "</html>";
		if (f.good())
		{
			f.close();
			return true;
		}
		else
		{
			f.close();
			return false;
		}
		
}

const char * System::getDes(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("INVALID INDEX TO GET TAG DES!\n");
	return tags[index]->getDes();
}

const char * System::getType(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("INVALID INDEX TO GET TAG TYPE!\n");
	return tags[index]->whatAmI();
}

void System::setFileName(const char * fileName)
{
	this->filename = fileName;

}

void System::setSize(size_t size)
{
	this->size = size;
}

void System::setCap(size_t cap)
{
	this->cap = cap;
}

void System::setTags(size_t size)
{
	this->tags = new Tag*[size];
}

void System::copyFrom(const System & other)
{
	
	setTags(other.cap);
	allToNull(other.cap);
	try
	{
		for (size_t i = 0; i < other.size; ++i)
			tags[i] = other.tags[i]->clone();
	}
	catch (const std::bad_alloc&)
	{
		clean(tags,other.size);
		throw;
	}
	setSize(other.size);
	setCap(other.cap);
	setFileName(other.filename);
}

void System::clean(Tag**&tags,size_t cap)
{
	for (size_t i = 0; i < cap; ++i)
		delete tags[i];
	delete[]tags;
	tags = nullptr;
}

void System::resize(size_t newCap)
{
	Tag**temp = tags;
	setTags(newCap);
	allToNull(newCap);

	size_t min = std::min(newCap, size);
	try
	{
		for (size_t i = 0; i < min; ++i)
			tags[i] = temp[i]->clone();
	}
	catch (const std::bad_alloc&)
	{
		clean(tags, min);
		tags = temp;
		throw;
	}

	clean(temp, cap);
	setCap(newCap);
}

void System::allToNull(size_t size)
{
	for (size_t i = 0; i < size; ++i)
		tags[i] = nullptr;
}
