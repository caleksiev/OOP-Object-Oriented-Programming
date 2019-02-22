#include "Picture-Post.h"

Picture_Post::Picture_Post(const char * content):Post(content)
{
}

bool Picture_Post::makeHTMLfile(std::ostream&f)const
{
	if (!f.good())
		return false;
	f << "<p>" << "<img src=" << "\"" << content << "\""
		<< "width=" << "\"" << "400" << "\"" << "height=" << "\"" << "200" << "\"" << ">" << "</p>";
	if (f.good())
		return true;
	return false;
}

Post * Picture_Post::clone ()const
{
	return new Picture_Post(*this);
}
