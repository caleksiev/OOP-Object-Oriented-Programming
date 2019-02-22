#include "Text-Post.h"

Text_Post::Text_Post(const char * text):Post(text)
{
}

bool Text_Post::makeHTMLfile(std::ostream &f) const
{
	if (!f.good())
		return false;
	f << "<p>" << content << "</p>";
	if (f.good())
		return true;
	return false;
}

Post * Text_Post::clone() const
{
	return new Text_Post(*this);
}
