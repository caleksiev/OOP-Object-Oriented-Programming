#include "Attribute.h"

Attribute::Attribute(const char * name, const char * value):value(nullptr)
{
	if (!name || !value)
		throw std::invalid_argument("NULL PTR PASS TO ATTRIBUTE CTOR");
	setValue(value);
	setName(name);
}

Attribute::Attribute(const Attribute & other):value(nullptr)
{
	copyFrom(other);
}

Attribute & Attribute::operator=(const Attribute & other)
{
	if (this != &other)
	{
		
		char*oldValue = value;
		copyFrom(other);
		delete[]oldValue;
	}
	return *this;
}

Attribute::~Attribute()
{
	clean();
}

Attribute * Attribute::clone() const
{
	return new Attribute(*this);
}

void Attribute::copyFrom(const Attribute & other)
{
	setValue(other.value);
	setName(other.name);
}

void Attribute::clean()
{
	delete[]value;
	value = nullptr;
}

void Attribute::setName(const char * name)
{
	strcpy(this->name, name);
}

void Attribute::setValue(const char * value)
{
	this->value = new char[strlen(value) + 1];
	strcpy(this->value, value);
}
