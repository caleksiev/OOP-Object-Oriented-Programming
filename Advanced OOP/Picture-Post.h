#ifndef _PICPOST_HEADER_INCLUDED_
#define _PICPOST_HEADER_INCLUDED_
#include"Post.h"
class Picture_Post:public Post
{
public:
	Picture_Post(const char*content);//to do:check if the  path image is correct
public:
	//�� ������� �����,�� ����������� � html ����,������������� ���� ������� ���
	//��� ��� ������� � ������ � �������� ��� ���� ����������� �� ����� false
	virtual bool makeHTMLfile(std::ostream&)const;
  //������� ��������� �������� ����� �� ������� �����
  //��� ���� ���������� ����� �� ������ ���������� std::bad_alloc(),������� ���� ������ �� �� ��������
	virtual Post*clone()const;
};
#endif
