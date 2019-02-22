#ifndef _MENU_HEADER_INCLUDED
#define _MENU_HEADER_INCLUDED
#include"System.h"
class Validation
{
public:
	static Validation& getInstance();
public:
	//по даден поток съобщава за необходимата информация
	void infoCommand(std::ostream & os)const;
	//връщат стринг,съобщаващ за резултата от всяка команда
	const char*addUsersCommand(const char*sbjName, const char*action, const char*objName, size_t age);
	const char*removeUsersCommand(const char*sbjName, const char*objName);
	const char*blockUnblockCommand(const char*sbjName, const char*objName, bool block_inblock);
	const char*addPostCommand(const char*sbjName,const char*type, const char*content, const char*des = NULL);
	const char*removePostCommand(const char*sbjName, size_t ID);/////
	const char*makeHTMLCommand(const char*sName, size_t ID);
	const char*makeHTMLallCommand(const char*sbjName, const char*objName);
	const char*renameCommand(const char*sbjName, const char*newName);
private:
	Validation();
	Validation(const Validation&) = delete;
	Validation& operator=(const Validation&) = delete;
private:

    //намира индекса на собственика на поста и го променя ID на поста зависимост от вътрешната номерация на системата
    //ако не намери поста връща отрицателен индекс
	int searchPost(size_t* ID, size_t* PostsOf)const;
	int checkNameExist(const char*name)const;
	//по подадените параметри записва индекса най най-младия/стария потребител
	void findOldYoungUser(size_t*oldest, size_t*youngest,size_t size)const;
	size_t cntBlockUsers(size_t)const;
private:
	System system;
};
#endif