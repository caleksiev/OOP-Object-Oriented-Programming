#ifndef _POSTFACT_HEADER_INCLUDED_
#define _POSTFACT_HEADER_INCLUDED_
#include"Link-Post.h"
#include"Picture-Post.h"
#include"Text-Post.h"
class PostFactory
{
public:
	static Post*createPost(const char*type, const char*content, const char*description = NULL)
	{
		if (!strcmp(type, "[url]"))
			return new Link_Post(content, description);
		else if (!strcmp(type, "[text]"))
			return new Text_Post(content);
		else  if (!strcmp(type, "[image]"))
			return new Picture_Post(content);
		else
			return NULL;
	}
};
#endif
