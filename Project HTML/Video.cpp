#include "Video.h"

Video::Video(const char * des, const char * text):Tag(des,text)
{

}

const char * Video::whatAmI() const
{
	return "video";
}

Tag * Video::clone()const
{
	return new Video(*this);
}

bool Video::writeOnHile(std::ostream & os)const
{
	if (!os)
		return false;
	os << "<p><iframe src="<<"\"" << content<<"\"" << " descr=" << "\"" << description << "\"";
	for (size_t i = 0; i < size && os.good(); ++i)
	{
		os << attribute[i]->getName() << "=" << "\""
			<< attribute[i]->getValue() << "\"";
	}
	os <<">"<< "</iframe>" << "</p>" << "\n";

	if (os.good())
		return true;
	else
		return false;
}
