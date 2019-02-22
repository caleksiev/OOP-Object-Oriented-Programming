#ifndef _PICPOST_HEADER_INCLUDED_
#define _PICPOST_HEADER_INCLUDED_
#include"Post.h"
class Picture_Post:public Post
{
public:
	Picture_Post(const char*content);//to do:check if the  path image is correct
public:
	//по подаден поток,се визуализира в html файл,изборажението чрез неговия път
	//ако има проблем с потока в началото или след обработката се връща false
	virtual bool makeHTMLfile(std::ostream&)const;
  //създава динамично заделено копие на текущия обект
  //ако няма достатъчно памет се хвърля изключение std::bad_alloc(),външния свят трябва да го прихване
	virtual Post*clone()const;
};
#endif
