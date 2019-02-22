#ifndef _TEXTPOST_HEADER_INCLUDED_
#define _TEXTPOST_HEADER_INCLUDED_
#include"Post.h"

class Text_Post:public Post
{
public:
	Text_Post(const char*text);
public:
	//по подаден поток,запива в html файл,съдържанието на поста
	//ако има проблем с потока в началото или след обработката се връща false
	virtual bool makeHTMLfile(std::ostream&)const;
	//създава динамично заделено копие на текущия обект
	//ако няма достатъчно памет се хвърля изключение std::bad_alloc(),външния свят трябва да го прихване
	virtual Post*clone()const;
};
#endif