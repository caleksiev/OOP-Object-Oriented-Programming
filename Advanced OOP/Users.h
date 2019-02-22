#ifndef _USERS_HEADER_INCLUDED
#define _USERS_HEADER_INCLUDED
#include"PostFactory.h"
#include"Result.h"

class Users
{
	friend	class System;//���� �� ������ �� ������� ��������������� ����� �� ������� � �����
	//�� ����� �� ������� ���� ��-�����,������ �� ������� ����������
public:
	//��� ��������� ������ � ��������� �� ������ ����������,std::invalid_argument
	Users(const char*name, size_t age);
	Users(const Users&other);
	Users& operator=(const Users&other);
	virtual ~Users();
public:
	//����� ��� ���������� �������� �� ���� � ��� �����,�������� �������
/*
	��� ���� ����� �� ���������� �� ������ std::bad_alloc()
	� ������ �� �� �������� ��������� ��������� �� ������ ����������,std::invalid_argument
	� ������ �� ��������� �� ������  ������ �� �������������,��� ���� ����� �� ������ std::bad_alloc()
	� ������ �� ����������� � ��������,�� �������� ����������� �� �����
	��������� �� ����� ��� ������� �� ��������� ������ ��� :)
*/
	Result addPost(const char*type,const char*content,const char*description=NULL);

/*
�� ����� ������,�� ��������� ������������,���� �� ������� ���-������ �� ������ � �� ������ ���� �� �������� �������
��� �������� � ��������� �� ������ ���������� std::invalid_argument
��� ���� ������ ���������� �� ���������� �� ������ ���������� std::length_error
�����!!! � ������,�� �� ������ ������������,�� �� �������� ���������� ID �� ������� �������
� ������,�� �� ������ �������� ���� � ������ 3,�� ���� �� ������� 3 �� ���� ���� � ������ 4 � �.�
������,������������ ��������� ������ �� ������� ����� �� �������� ��������� ������� �� ��������� ���� ���������
*/	
	void removePost(size_t index);


   //��� �� ������ ��������� ������ �� ������ ���������� std::invalid_argument
   //��� ����� �������� �� �������� � ����� �� ����� �� ����� false

	bool makeHtmlFile(size_t index);

	//���������� �� �������,���� �� �� �������� ������ ������� �� �����������
	Result makeHtmlAllFile();

	
public:
	virtual Users*clone()const = 0;
public:
	virtual bool canBlockUnblock()const=0;
	virtual bool canAdd()const = 0;
	virtual bool canRemove()const = 0;
public:

public:
	//������
	const char*getName()const;
	bool getStatus()const;
	size_t getAge()const;
	size_t getCntPosts()const;
	size_t getID(size_t index)const;

/*
������ �� � ������ �� �������� �� ���������� ��������� ��������� �� ������ �� �� �� �������
��� ������� �������� �� ��� �������->������� ���������  ��� ��������� ������ �� ������ ����� �� ������
*/
	void resize(size_t newCap);
	void copyFrom(const Users&other);
	

	void allToNull(size_t size);
	void clearAll();
	void clearName();
	void clearPosts();
	void clearTemp(Post**&post);


private:
	//������
	void setAge(const size_t age);
	void setIsBlock(bool isBlock);
	void setCurrPosts(size_t cnt);
	void setRealPosts(size_t cnt);
	//�� ���������,�� ����� ���� �� � �����,����� � �� ������� ����
	void setName(const char*name);
private:
	Post**posts;
	size_t cntCurrPosts;//�������� ������,�������� �� ������� ����
	size_t cntRealPosts;//�������� ������ �� ���������� � ������ ����� �� �������
	char*name;
	size_t age;
	bool isBlocked;//��������� �� ���� ���� ����������� � �������� ��� ��
};
#endif
