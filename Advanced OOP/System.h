#ifndef _SYSTEM_HEADER_INCLUDED
#define _SYSTEM_HEADER_INCLUDED
#include"UsersFactory.h"
class System
{
public:
	System(const char*adminName, size_t adminAge);
	~System();
public:
	//във всички функции подаваме управлението на класа Users,тъй той носи
	//отговорност за данните на потребителите,включително постовете
	Result addPost(size_t poster,const char*type, const char*content, const char*des=NULL);
	void removePost(size_t remover, size_t postID);
	bool makeHtmlFile(size_t receiver, size_t postID);
	Result makeAllFtmlFile(size_t receiver);

public:
	//за това вече се грижи системата
	bool addUser(const char*type, const char*name, size_t age, size_t indexWho);//ok
	Result removeUser(size_t remover, size_t removed);
	Result blockUnblockUser(size_t blocker, size_t blocked, bool flag);
	void rename(size_t index, const char*newName);
public:
	//гетъри
	const char*getName(size_t index)const;
	size_t getCurrUsers()const;
	size_t getAge(size_t index)const;
	bool getStatus(size_t index)const;
	size_t getCntPosts(size_t index)const;
	size_t getUserPostsID(size_t indexU, size_t indexP)const;
public:
	bool isModerator(size_t index)const ;
private:
	System(const System&) = delete;
	System&operator=(const System&) = delete;
private:
	void allToNullPtr(size_t size);
	void clearUsers(Users**&users);
	void resize(size_t newCap);
private:
	//аналогични данни както при постовете
	Users**users;
	size_t cntCurrUsers;
	size_t cntRealUsers;
};
#endif
