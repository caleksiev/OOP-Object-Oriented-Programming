#include "Image.h"

Image::Image(const char * des, const char * text):Tag(des,text)
{

}

const char * Image::whatAmI() const
{
	return "image";
}

Tag * Image::clone()const
{
	return new Image(*this);
}

bool Image::writeOnHile(std::ostream & os)const
{
	if (!os)
		return false;
	os << "<p><img src=" << "\"" << content << "\"" << " descr=" << "\"" << description << "\"";
	for (size_t i = 0; i < size && os.good(); ++i)
	{
		os << attribute[i]->getName() << "=" << "\""
			<< attribute[i]->getValue() << "\"";
	}
	os << ">" << "</p>" << "\n";

	if (os.good())
		return true;
	else
		return false;
}
