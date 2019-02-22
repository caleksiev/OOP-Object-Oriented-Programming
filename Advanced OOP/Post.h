#define _CRT_SECURE_NO_WARNINGS
#ifndef _POST_HEADER_INCLUDED_
#define _POST_HEADER_INCLUDED_
#include<cstring>
#include<iostream>
#include<fstream>
#include<exception>
class Post
{
public:
	//ако се подаде невалиден ptr за съдържание се хвърля изключение std::invalid_argument
	Post(const char*content);
	Post(const Post&other);
	//само когата успешно са прехвърлени данните от другия обект се почивства информацията за текущия
	Post& operator=(const Post&other);
	virtual ~Post();
public:
	//всеки вид пост се грижи за създаването на файла и клонирането по различен начин
	//сам по-себе си поста няма смисъл,затова е абстрактен
	virtual bool makeHTMLfile(std::ostream&)const = 0;
	virtual Post*clone()const=0;
public:
	size_t getID()const;
	static size_t getCnt();
private:
	void setContent(const char*content);
	void setID(size_t ID);
private:
	void copyFrom(const Post&other);
protected:
	//осигурява се защитен достъп до наследниците,в случай че там нещо се обърка да си почистят и базовите данни
	void clean();
protected:
	char*content;//съдържанието на поста(текст,линк или абсолютния път до изображение)
private:
	size_t ID;//уникалното ID на поста
	static size_t cnt;//системния брой създадени публикации,от които ще се интересува външния свят
};
#endif