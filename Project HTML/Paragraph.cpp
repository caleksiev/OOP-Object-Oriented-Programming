#include "Paragraph.h"

Paragraph::Paragraph(const char * des, const char * text):Tag(des,text)
{

}

const char * Paragraph::whatAmI() const
{
	return "text";
}

Tag * Paragraph::clone()const
{
	return new Paragraph(*this);
}

bool Paragraph::writeOnHile(std::ostream & os)const
{
	if (!os)
		return false;
	os << "<p" << " descr=" << "\"" << description << "\"";
	for (size_t i = 0; i < size && os.good(); ++i)
	{
		os << attribute[i]->getName() << "=" << "\"" 
			<< attribute[i]->getValue() << "\"";
	}
	os << ">" << content << "</p>" << "\n";
	if (os.good())
		return true;
	else
		return false;
}
