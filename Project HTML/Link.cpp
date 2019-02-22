#include "Link.h"

Link::Link(const char * des, const char * text,const char*linkDes):Tag(des,text),linkDes(nullptr)
{
	setLinkDes(linkDes);
}

Link::Link(const Link & other):Tag(other),linkDes(nullptr)
{
	copyFrom(other);
}

Link & Link::operator=(const Link & other)
{
	if (this != &other)
	{
		Tag::operator=(other);
		char*oldLinkDes = linkDes;
		copyFrom(other);
		delete[]oldLinkDes;
	}
	return *this;
}

Link::~Link()
{
	clean();
}

const char * Link::whatAmI() const
{
	return "link";
}

Tag * Link::clone() const
{
	return new Link(*this);
}

bool Link::writeOnHile(std::ostream & os)const
{
	if (!os)
		return false;
	os << "<p><a href=" << "\"" << content << "\"" << " descr=" << "\"" << description << "\"";
	for (size_t i = 0; i < size && os.good(); ++i)
	{
		os << attribute[i]->getName() << "=" << "\""
			<< attribute[i]->getValue() << "\"";
	}
	os << ">" << linkDes << "</a></p>" << "\n";

	if (os.good())
		return true;
	else
		return false;
}

void Link::clean()
{
	delete[]linkDes;
	linkDes = nullptr;
}

void Link::copyFrom(const Link & other)
{
	setLinkDes(other.linkDes);
}

void Link::setLinkDes(const char * linkDes)
{
	this->linkDes = new char[strlen(linkDes) + 1];
	strcpy(this->linkDes, linkDes);
}
