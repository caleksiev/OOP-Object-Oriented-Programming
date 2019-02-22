#ifndef FACT_HEAFER_INCLUDED
#define FACT_HEAFER_INCLUDED
#include"Heading.h"
#include"Video.h"
#include"Link.h"
#include"Image.h"
#include"Paragraph.h"
class TagFactory
{
public:
	static Tag*createTag(const char*command,const char*des,const char*content,
		const char*linkDes=0,unsigned short headSize=0)
	{
		if (!strcmp(command, "heading"))
			return new Heading(des, content, headSize);
		else if (!strcmp(command, "text"))
			return new Paragraph(des, content);
		else if (!strcmp(command, "image"))
			return new Image(des, content);
		else if (!strcmp(command, "video"))
			return new Video(des, content);
		else if (!strcmp(command, "link"))
			return new Link(des, content, linkDes);
		else
			return nullptr;
	}
};
#endif
