#ifndef _USERS_HEADER_INCLUDED
#define _USERS_HEADER_INCLUDED
#include"PostFactory.h"
#include"Result.h"

class Users
{
	friend	class System;//лошо но трябва да достъпи потребителската данна за статуса и името
	//не успях да измисля нещо по-добро,затова го оставих приятелски
public:
	//ако подадения стринг е невалиден се хвърля изключение,std::invalid_argument
	Users(const char*name, size_t age);
	Users(const Users&other);
	Users& operator=(const Users&other);
	virtual ~Users();
public:
	//всеки вид потребител използва по един и същ начин,следните команди
/*
	ако няма памет за операцията се хвърля std::bad_alloc()
	в случай че са подадени невалидни аргументи се хвърля изключение,std::invalid_argument
	в случай на достигане на лимита  масива се преоразмерява,ако няма памет се хвърля std::bad_alloc()
	в случай че потребителя е блокиран,се отхвърля записването на поста
	резултата се връща под формата на разбираем избром тип :)
*/
	Result addPost(const char*type,const char*content,const char*description=NULL);

/*
по даден индекс,се отсранява публикацията,като се постави най-накрая на масива и се намали броя на текущите постове
ако индексът е невалиден се хвърля изключение std::invalid_argument
ако няма повече публикации за премахване се хвърля изключение std::length_error
ВАЖНО!!! в случай,че се изтрие публикацията,не се променят уникалните ID на другите постове
В случай,че се изтрие например пост с индекс 3,то вече на позиция 3 ще бъде пост с индекс 4 и т.н
външно,изплозващите функцията трябва да намерят начин да маркират изтритите индекси на постовете като невалидни
*/	
	void removePost(size_t index);


   //ако се подаде невалиден индекс се хвърля изключение std::invalid_argument
   //ако някоя операция по работата с файла не успее се връща false

	bool makeHtmlFile(size_t index);

	//аналогична на горната,само че се записват всички постове на потребителя
	Result makeHtmlAllFile();

	
public:
	virtual Users*clone()const = 0;
public:
	virtual bool canBlockUnblock()const=0;
	virtual bool canAdd()const = 0;
	virtual bool canRemove()const = 0;
public:

public:
	//гетъри
	const char*getName()const;
	bool getStatus()const;
	size_t getAge()const;
	size_t getCntPosts()const;
	size_t getID(size_t index)const;

/*
грижат се в случай на хвърляне на изключение валидното състояние на обекта да не се промени
под валидно състояни се има предвид->Валидни стойности  или дефоултни такива за всички данни на обекта
*/
	void resize(size_t newCap);
	void copyFrom(const Users&other);
	

	void allToNull(size_t size);
	void clearAll();
	void clearName();
	void clearPosts();
	void clearTemp(Post**&post);


private:
	//сетъри
	void setAge(const size_t age);
	void setIsBlock(bool isBlock);
	void setCurrPosts(size_t cnt);
	void setRealPosts(size_t cnt);
	//не гарантира,че името вече не е заето,грижа е на външния свят
	void setName(const char*name);
private:
	Post**posts;
	size_t cntCurrPosts;//текущата бройка,известна за външния свят
	size_t cntRealPosts;//реалната бройка на заделените в масива места за постове
	char*name;
	size_t age;
	bool isBlocked;//индикация за това дали потребителя и блокиран или не
};
#endif
