#ifndef _TEXTPOST_HEADER_INCLUDED_
#define _TEXTPOST_HEADER_INCLUDED_
#include"Post.h"

class Text_Post:public Post
{
public:
	Text_Post(const char*text);
public:
	//�� ������� �����,������ � html ����,������������ �� �����
	//��� ��� ������� � ������ � �������� ��� ���� ����������� �� ����� false
	virtual bool makeHTMLfile(std::ostream&)const;
	//������� ��������� �������� ����� �� ������� �����
	//��� ���� ���������� ����� �� ������ ���������� std::bad_alloc(),������� ���� ������ �� �� ��������
	virtual Post*clone()const;
};
#endif