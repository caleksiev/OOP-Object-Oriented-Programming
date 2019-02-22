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
	//��� �� ������ ��������� ptr �� ���������� �� ������ ���������� std::invalid_argument
	Post(const char*content);
	Post(const Post&other);
	//���� ������ ������� �� ����������� ������� �� ������ ����� �� ��������� ������������ �� �������
	Post& operator=(const Post&other);
	virtual ~Post();
public:
	//����� ��� ���� �� ����� �� ����������� �� ����� � ����������� �� �������� �����
	//��� ��-���� �� ����� ���� ������,������ � ����������
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
	//��������� �� ������� ������ �� ������������,� ������ �� ��� ���� �� ������ �� �� �������� � �������� �����
	void clean();
protected:
	char*content;//������������ �� �����(�����,���� ��� ���������� ��� �� �����������)
private:
	size_t ID;//���������� ID �� �����
	static size_t cnt;//��������� ���� ��������� ����������,�� ����� �� �� ���������� ������� ����
};
#endif