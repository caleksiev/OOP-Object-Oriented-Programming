#include"Menu.h"
/*
���������� ��� ��������� �� 5 ����:
0)��������� ��nu-����� �� �� ������� �� ��������� � ������������� �� ������������ �������
1)������ Validation-�������� ����������,��������� �� Menu � ���� ��������� �����,����� ������ ��������� ��������� ��
��������� �� ����������� ���������� � ��������� 2),3) ��� 4),����������� �� ���������
2)������ �������-����� �� �� ������������� � ���������-������� ��������,���������/�������������,���������� � ������������
3)������ ����������-����� �� �� ��������� �� ����� ����������,������� �������� � ����������
4)������ ����,����� ������ � �� �����������,����������� ������� � HTML ����
/////////////////
�������� �� ���������� �� ����� �� ������ ,� main �� �������� � �������� �� ���� ���� ����� ���������� ���������
������� �� ������ ������� ������ ������� �� bad_alloc � ���� ������ �� ������ ���� ���� ���������
� ���� �� �������� ���� ���� ������
*/

int main()
{
	std::cout << "The allowed commad are:\n"
		<< "1:<ACTOR-NAME> <add_moderator/add_users> <SUBJECT-NAME>  <AGE>\n"
		<< "2:<ACTOR-NAME> <remove_user> <SUBJECT-NAME>\n"
		<< "3:<ACTOR-NAME> <block/unblock> <SUBJECT-NAME>\n"
		<< "4:<ACTOR-NAME> <post> <[image]/[url]/[text]> <CONTENT/CONTENT AND DESCR/CONTENT/>\n"
		<< "5:<ACTOR-NAME> <remove_post> <ID>\n"
		<< "6:<ACTOR-NAME> <view_post><ID>\n"
		<< "7:<ACTOR-NAME> <view_all_posts><SUBJECT-NAME>\n"
		<< "8:<ACTOR-NAME> <rename> <NEW-NAME>\n"
		<< "9:<info>\n"
		<< "10:<quit>\n";
	try
	{
		Menu();
	}
	catch (const std::exception &e)
	{
		e.what();
	}
	return 0;
}