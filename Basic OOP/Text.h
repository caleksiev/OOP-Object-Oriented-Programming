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
	//имплементирал съм ги,въпреки че за момента не ми трябват
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

	//когато се достигне CurrRows==RealRows,масива се прави 2пъти по-голям
	//или съответно когато се премахнат определен брой редове масивът се стеснява 2 пъти
	void resize(size_t newcap);

private:
	const char*filename;
	Row*rows;
	size_t CurrRows;//текущото заделено място за редове, което потребителя е запълнил
	size_t RealRows;//реалното,заделено място за редовете
};
#endif
