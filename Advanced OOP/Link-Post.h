#ifndef _LINKPOST_HEADER_INCLUDED_
#define _LINKPOST_HEADER_INCLUDED_
#include"Post.h"
class Link_Post:public Post
{
public:
	//ако се подаде невалиден пойнтър за описание се хвърля изключение std::invalid_argument
	Link_Post(const char*content, const char*description);
	Link_Post(const Link_Post& other);
	Link_Post& operator=(const Link_Post&othet);//to do:fix exep
	~Link_Post();
public:
	//по подаден поток,записва в html файл,съдържанието на поста,(директен достъп до линка със съответното описание)
	//ако има проблем с потока в началото или след обработката се връща false
	virtual bool makeHTMLfile(std::ostream&)const;
	//създава динамично заделено копие на текущия обект
	//ако няма достатъчно памет се хвърля изключение std::bad_alloc(),външния свят трябва да го прихване
	virtual Post*clone()const;
private:
	void setDes(const char*des);
private:
	void copyFrom(const Link_Post&other);
	void clean();
private:
	char*description;//конкретно описание на съдържанието в линка
};
#endif
