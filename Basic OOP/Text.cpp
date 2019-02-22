#include "Text.h"
//temp function that simulate the work of strcpy
void strcpy_newContentH(const char*from, char*to, size_t len);

Text::Text(const char * filename)
{
	if (!isValidFPath(filename))
		throw "Unvalid file path!";
	setFilename(filename);
	int cnt = cntRowsFromFile(filename);
	if (!cnt)
		throw "File is empty!";
	else if (cnt < 0)
		throw "Problem while reading from file!";
	else
		++cnt;
	setCurrRows(cnt);
	setRealRows(cnt * 2);
	rows = new Row[RealRows];
	setRowsFromFile(filename);
}

Text::~Text()
{
	clean();
}

///////////////////////////////////////
void Text::MakeHeading(size_t line)
{
	if (!IsValidLineHeading(line))
		return;

	const char*tempWord = rows[line - 1].getWord(0);
	size_t wordLen = strlen(tempWord);
	char*newWord = new char[wordLen + 1 + 1];
	strcpy_newContentH(tempWord, newWord, wordLen);

	const char*tempRow = rows[line - 1].getContent();
	size_t rowLen = strlen(tempRow) ;
	char*newRow = new (std::nothrow)char[rowLen + 1+1];//+1 for "#
	if (!newRow)
	{
		delete newWord;
		throw std::bad_alloc();
	}
	strcpy_newContentH(tempRow, newRow, rowLen);

	try
	{
		rows[line - 1].setNewWord(newWord, 0);
		rows[line - 1].setContent(newRow);
	}
	catch (...)
	{
		delete[]newWord;
		delete[]newRow;
		throw;
	}
	//няма грешки всичко е приключило нормално
	delete[] newRow;
	delete[]newWord;

	//не съм много сигурен дали трябва да се прави това
	for (size_t i = line - 1; i > 0; i--)
	{
		Row temp = rows[i];
		rows[i] = rows[i - 1];
		rows[i - 1] = temp;
	}
	std::cout << "The row is now a HEADING!\n";
}

void Text::AddLine(const char * line)
{
	if (line == nullptr)line = "UKNOWN ROW :)";
	if (!strcmp(line, ""))line = "EMPTY ROW";
	if (CurrRows == RealRows)
	{
		resize(RealRows*2);
	}
	Row temp(line);
	rows[CurrRows++] = temp;
	std::cout << "The line is successfully added!\n";
}

void Text::Remove(size_t line)
{
	if (!IsValidLineRemove(line))
		return;
	for (size_t i = line - 1; i < CurrRows - 1; i++)
		std::swap(rows[i], rows[i + 1]);
	--CurrRows;//сигурни сме че няма да стане  нула
	if (CurrRows * 2 <= RealRows)
	resize(RealRows / 2);
	std::cout << "The line is succsessfully remove!\n";
}

void Text::MakeBold(size_t line, size_t from, size_t to)
{
	MakeFont(line, from, to, 'b');
}

void Text::MakeItalic(size_t line, size_t from, size_t to)
{
	MakeFont(line, from, to, 'i');
}

void Text::MakeCombine(size_t line, size_t from, size_t to)
{
	MakeFont(line, from, to, 'c');
}

void Text::SaveToNewFormat()
{
	const char*newfilename = ChangeFileFormat(filename);
	std::fstream f;
	f.open(newfilename, std::ios::out);
	for (size_t i = 0; i < CurrRows; ++i)
	{
		if (!f.good())
			throw "Error while writting on file!\n";
		rows[i].serialize(f);
	}
}
//////////////////////////////////////////////

Text::Text(const Text & other)
{
	copyFromOther(other);
}
Text & Text::operator=(const Text & other)
{
	if (this != &other)
	{
		clean();
		copyFromOther(other);
	}
	return*this;
}
void Text::copyFromOther(const Text & other)
{
	setFilename(other.filename);
	setCurrRows(other.CurrRows);
	setRealRows(other.RealRows);
	this->rows = new Row[other.RealRows];//
	for (size_t i = 0; i < CurrRows; i++)
	{
		this->rows[i] = other.rows[i];
	}
}
void Text::clean()
{
	delete[]rows;
	rows = nullptr;
	filename = nullptr;
	CurrRows = 0;
	RealRows = 0;
}


void Text::setFilename(const char*filename)
{
	this->filename = filename;
}
void Text::setCurrRows(size_t csize)
{
	this->CurrRows = csize;
}
void Text::setRealRows(size_t rsize)
{
	this->RealRows = rsize;
}
void Text::setRowsFromFile(const char*filename)
{
	try
	{
		if (!CopyFromFile(filename))
			throw "Problem while reading from file!";
	}
	catch (...)
	{
		delete[]rows;
		throw;
	}

}

bool Text::isValidFPath(const char*filename)const
{
	std::fstream f;
	f.open(filename, std::ios::in);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	f.close();
	return false;
}
bool Text::IsValidLineHeading(size_t line)const
{
	if (line > CurrRows || !line)
	{
		std::cout << "There is no a such row in a file!\n";
		return false;
	}
	const char*content = rows[line - 1].getContent();
	if (content[0] == '#')
	{
		std::cout << "Already Heading!\n";
		return false;
	}
	return true;
}
bool Text::IsValidLineRemove(size_t line)const
{
	if (CurrRows == 0)
		throw "The file is empty!\n";
	if (line > CurrRows || line == 0)
	{
		std::cout << "There is no a such line in a file!\n";
		return false;
	}
	return true;
}
bool Text::IsValidLineToFromFont(size_t line, size_t from, size_t to)const
{
	if (line > CurrRows || line == 0)
	{
		std::cout << "There is no a such row in a file\n";
		return false;
	}
	size_t lenwords = rows[line - 1].getCnt();

	if (from > to || to > lenwords || from > lenwords)
	{
		std::cout << "Wrong interval from words!\n";
		return false;
	}
	///////////
	const char*oldWord_from = rows[line - 1].getWord(from - 1);
	const char*oldWord_to = rows[line - 1].getWord(to - 1);
	size_t lenFrom = strlen(oldWord_from);
	size_t lenTo = strlen(oldWord_to);
	if (oldWord_from[0] == '*' || oldWord_from[1] == '*')
	{
		std::cout << "One or more of the words in the given inteval is already transform with this font!\n";
		std::cout << "Give a interval that not contant for example the word:" << oldWord_from;
		return false;
	}
	if (oldWord_to[0] == '*' || oldWord_to[1] == '*')
	{
		std::cout << "One or more of the words in the given inteval is already transform with this font!\n";
		std::cout << "Give a interval that not contant for example the word:" << oldWord_to << std::endl;
		return false;
	}
	return true;
}

int Text::cntRowsFromFile(const char*filename)const
{
	char temp[MAX_LEN + 1] = { 0, };
	size_t cnt = 0;
	std::fstream f;
	f.open(filename, std::ios::in);
	if (!f.is_open())
		return -1;
	while (f.good())
	{
		f.getline(temp, 1024);
		if (f.good())++cnt;
	}
	if (f.eof())
	{
		f.close();
		return cnt;
	}
	else//the error is else//bad:(
	{
		f.close();
		return -1;
	}
}
bool Text::CopyFromFile(const char*filename)
{
	char temp[MAX_LEN + 1] = { 0, };
	std::fstream f;
	f.open(filename, std::ios::in);
	if (!f.is_open())
		return false;
	for (size_t i = 0; i < CurrRows && f.good(); i++)
	{
		rows[i].deserialize(f);
	}
	if (f.eof())
	{
		f.close();
		return true;
	}
	else
	{
		f.close();
		return false;
	}
}
const char * Text::ChangeFileFormat(const char * filename)
{
	size_t size = strlen(filename);
	char*newfilename = new char[size];//we replace "txt" with md
	newfilename[size - 1] = '\0';
	newfilename[size - 2] = 'd';
	newfilename[size - 3] = 'm';

	for (int i = size - 4; i >= 0; --i)
	{
		newfilename[i] = filename[i];
	}

	return newfilename;
}

void Text::MakeFont(size_t line, size_t from, size_t to, char s)
{
	
	if (!(IsValidLineToFromFont(line, from, to)))
		return;

	const char*oldWord_from = rows[line - 1].getWord(from - 1);
	size_t lenFrom = strlen(oldWord_from);

	const char*oldWord_to = rows[line - 1].getWord(to - 1);
	size_t lenTo = strlen(oldWord_to);
	//тук ще запишем новите преработена думи 
	char*newWord_from = nullptr;
	char*newWord_to = nullptr;

	//в функцията ChangeWords заделяме памет за новата дума с определените индентификатори
	if (from == to)
	{
		ChangeWords(newWord_from, oldWord_from, lenFrom, s,1);
		rows[line - 1].setNewWord(newWord_from, from-1);
		delete[]newWord_from;
	}
	else
	{
		ChangeWords(newWord_from, oldWord_from, lenFrom, s,2);
		ChangeWords(newWord_to, oldWord_to, lenTo, s, 3);
		try
		{
		rows[line - 1].setNewWord(newWord_from, from-1);
		rows[line - 1].setNewWord(newWord_to, to - 1);
		}
		catch (...)
		{
			delete[]newWord_from;
		}
		delete[]newWord_from;
		delete[]newWord_to;
	}
	////////////
	const char*oldRow = rows[line - 1].getContent();
	size_t newlen = strlen(oldRow);
	
	//в зависимост от избрания шрифт добавяме толкова място са броя на звездите
	if (s == 'i')
		newlen += 2;
	else if (s == 'b')
		newlen += 4;
	else
		newlen += 6;

	char*newRow = new char[newlen + 1];
	CreateNewRow(newRow, newlen, line);
	try
	{
		rows[line - 1].setContent(newRow);
	}
	catch (...)
	{
		delete newRow;
		throw;
	}
	delete newRow;
	std::cout << "The font is seccsessfully set!\n";
}
void Text::ChangeWords(char*&Words, const char*oldContent, size_t size, char s, size_t flag)const
{
	size_t from, to;
	switch (s)
	{
	case'i':
		if (flag == 1)
		{
			Words = new char[size + 2 + 1]; // +2 for both "*" at the beg and end of the word
			Words[0] = Words[size + 1] = '*';
			Words[size + 2] = '\0';
			from = 1;
			to = size + 1;
		}
		else
		{
			Words = new char[size + 1 + 1]; // +1 for  "*" at the beg or at end a of the words
			Words[size + 1] = '\0';
			if (flag == 2)
			{
				Words[0] = '*';
				from = 1;
				to = size + 1;
			}
			else
			{
				Words[size] = '*';
				from = 0;
				to = size;
			}
		}
		break;
	case'b':
		if (flag == 1)
		{
			Words = new char[size + 4 + 1]; // +4 for both "**" at the beg and end of the word
			Words[0] = Words[1] = '*';
			Words[size + 2] = Words[size + 3] = '*';
			Words[size + 4] = '\0';
			from = 2;
			to = size + 2;
		}
		else
		{
			Words = new char[size + 2 + 1]; // +2 for  "**" at the beg or at the end of the word
			Words[size + 2] = '\0';
			if (flag == 2)
			{
				Words[0] = Words[1] = '*';
				from = 2;
				to = size + 2;
			}
			else
			{
				Words[size] = Words[size + 1] = '*';
				from = 0;
				to = size;
			}

		}
		break;
	case'c':
		if (flag == 1)
		{
			Words = new char[size + 6 + 1]; //+6 for both "***" at the beg and end of the word
			Words[0] = Words[1] = Words[2] = '*';
			Words[size + 3] = Words[size + 4] = Words[size + 5] = '*';
			Words[size + 6] = '\0';
			from = 3;
			to = size + 3;
		}
		else
		{
			Words = new char[size + 3 + 1]; // +3 for  "***" at the beg ot at the end of the word
			Words[size + 3] = '\0';
			if (flag == 2)
			{
				Words[0] = Words[1] = Words[2] = '*';
				from = 3;
				to = size + 3;
			}
			else
			{
				Words[size] = Words[size + 1] = Words[size + 2] = '*';
				from = 0;
				to = size;
			}
		}
	}
	for (size_t i = from, j = 0; i < to; i++, j++)
	{
		Words[i] = oldContent[j];
	}

	//ако съдържа вече индикация за главен ред го преместваме отпред
	if (Words[1] == '#')
		std::swap(Words[1], Words[0]);
	else if (Words[2] == '#')
		std::swap(Words[2], Words[0]);
	else if (Words[3] == '#')
		std::swap(Words[3], Words[0]);
}
void Text::CreateNewRow(char*content, size_t len, size_t line)const
{
	content[len] = '\0';
	size_t index_word = 0;
	for (size_t i = 0; i < len; ++i)
	{
		const char*words = rows[line - 1].getWord(index_word);
		++index_word;
		for (size_t j = 0; words[j]; ++j, ++i)
		{
			content[i] = words[j];
		}
		if (i != len)content[i] = ' ';
	}
}

void Text::resize(size_t newcap)
{
	Row*temp = rows;
	rows = new Row[newcap];

	try
	{
		for (size_t i = 0; i < CurrRows; ++i)
			rows[i] = temp[i];
	}
	catch (...)
	{
		//ако нещо се обърка при оператор= връщаме нещата както са били
		delete rows;
		rows = temp;
	}
	delete[]temp;
	RealRows = newcap;
}

void strcpy_newContentH(const char*from, char*to, size_t len)
{
	to[0] = '#';
	for (size_t i = 0; i < len+1; i++)
	{
		to[i + 1] = from[i];
	}
}