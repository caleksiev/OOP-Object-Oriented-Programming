#include "Heading.h"

Heading::Heading(const char*des, const char * cont, unsigned short size) :Tag(des,cont)
{
	setSize(size);
	if(!(size>=1 && size<=6))
		throw std::invalid_argument("THE ALLOWED SIZE ARE IN THE INTERVAL 1-6!\n");
}


const char * Heading::whatAmI() const
{
	return "heading";
}

Tag * Heading::clone()const
{
	return new Heading(*this);
}

bool Heading::writeOnHile(std::ostream & os)const
{
	if (!os)
		return false;
	os << "<p><h" << char(sizeH + '0') << " descr=" << "\"" << description << "\"";
	for (size_t i = 0; i < size && os.good(); ++i)
	{
		os << attribute[i]->getName() << "=" << "\""
			<< attribute[i]->getValue() << "\"";
	}
	os << ">" << content << "</h" << char(sizeH + '0') << ">" << "</p>" << "\n";

	if (os.good())
		return true;
	else
		return false;
}


void Heading::setSize(unsigned short size)
{
	sizeH = size;
}
