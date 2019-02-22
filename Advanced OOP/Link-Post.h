#ifndef _LINKPOST_HEADER_INCLUDED_
#define _LINKPOST_HEADER_INCLUDED_
#include"Post.h"
class Link_Post:public Post
{
public:
	//��� �� ������ ��������� ������� �� �������� �� ������ ���������� std::invalid_argument
	Link_Post(const char*content, const char*description);
	Link_Post(const Link_Post& other);
	Link_Post& operator=(const Link_Post&othet);//to do:fix exep
	~Link_Post();
public:
	//�� ������� �����,������� � html ����,������������ �� �����,(�������� ������ �� ����� ��� ����������� ��������)
	//��� ��� ������� � ������ � �������� ��� ���� ����������� �� ����� false
	virtual bool makeHTMLfile(std::ostream&)const;
	//������� ��������� �������� ����� �� ������� �����
	//��� ���� ���������� ����� �� ������ ���������� std::bad_alloc(),������� ���� ������ �� �� ��������
	virtual Post*clone()const;
private:
	void setDes(const char*des);
private:
	void copyFrom(const Link_Post&other);
	void clean();
private:
	char*description;//��������� �������� �� ������������ � �����
};
#endif
