#define _CRT_SECURE_NO_WARNINGS
#ifndef _TEXT_HEADER_INCLUDED_
#define _TEXT_HEADER_INCLUDED_
#include"Row.h"
class Text
{
public:
	Text(const char*text);
	~Text();

	void MakeHeading(size_t line);
	void AddLine(const char*line);
	void Remove(size_t line);
	void MakeBold(size_t line, size_t from, size_t to);
	void MakeItalic(size_t line, size_t from, size_t to);
	void MakeCombine(size_t line, size_t from, size_t to);
	void SaveToNewFormat();

private:
	//������������� ��� ��,������� �� �� ������� �� �� �������
	Text();
	Text(const Text&other);
	Text& operator=(const Text&other);
	//temp function for copy ctor
	void copyFromOther(const Text&other);
	//temp function for dctor
	void clean();

	//setters
	void setFilename(const char*filename);
	void setCurrRows(size_t csize);
	void setRealRows(size_t rsize);
	void setRowsFromFile(const char*);

	//validating user's input
	bool isValidFPath(const char*filename)const;
	bool IsValidLineHeading(size_t line)const;
	bool IsValidLineRemove(size_t line)const;
	bool IsValidLineToFromFont(size_t line, size_t from, size_t to)const;

	//function that works with file
	bool CopyFromFile(const char*);
	int  cntRowsFromFile(const char*)const;
	const char *ChangeFileFormat(const char * filename);

	//temp function for changing the font
	void MakeFont(size_t line, size_t from, size_t to, char s);
	void CreateNewRow(char*content, size_t len, size_t line)const;
	void Text::ChangeWords(char*&Words, const char*oldContent, size_t size, char s, size_t flag)const;

	//������ �� �������� CurrRows==RealRows,������ �� ����� 2���� ��-�����
	//��� ��������� ������ �� ��������� ��������� ���� ������ ������� �� �������� 2 ����
	void resize(size_t newcap);

private:
	const char*filename;
	Row*rows;
	size_t CurrRows;//�������� �������� ����� �� ������, ����� ����������� � ��������
	size_t RealRows;//��������,�������� ����� �� ��������
};
#endif
