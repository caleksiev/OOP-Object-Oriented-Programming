#define _CRT_SECURE_NO_WARNINGS
#include "Row.h"
#include"Text.h"
Row::Row():content(nullptr),words(nullptr),cnt(0)
{

}
Row::Row(const char * content)
{
	setContent(content);
	setCnt(cntWords(content));
	setWords(content);
}
Row::Row(const Row & other):content(nullptr),words(nullptr)
{
	copyFrom(other);
}
Row & Row::operator=(const Row & other)
{
	if (this != &other)
	{
		clean();
		cleanMatrix(cnt);
		copyFrom(other);
	}
	return *this;
}

Row::~Row()
{
	cleanMatrix(cnt);
	clean();
}

void Row::setContent(const char*content)
{
	this->content = new char[strlen(content) + 1];
	strcpy(this->content, content);
}
void Row::setCnt(size_t cnt)
{
	this->cnt = cnt;
}
void Row::setWords(const char*content)
{
	try
	{
		words = new char*[cnt];
	}
	catch (const std::bad_alloc&)
	{
		clean();
		throw;
	}
	for (size_t i = 0; i < cnt; ++i)
	{
		while (*content && *content == ' ')
			++content;
		size_t cnt = 0;
		while (*content && *content != ' ')
		{
			++cnt;
			++content;
		}
		content -= cnt;
		if (!(words[i] = new(std::nothrow)char[cnt + 1]))
		{
			clean();
			cleanMatrix(i);
			throw std::bad_alloc();
		}
		words[i][cnt] = '\0';
		for (size_t j=0 ;j < cnt; ++j)
		{
			words[i][j] = *content;
			++content;
		}
		
	}
}
void Row::setNewWord(const char * word,size_t index)
{
	delete[]this->words[index];
	this->words[index] = new char[strlen(word) + 1];
	strcpy(this->words[index], word);
}

size_t Row::cntWords(const char*str)const
{
	size_t cnt = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			++str;
		if (*str)
			++cnt;
		while (*str && *str != ' ')
			++str;
	}
	return cnt;
}
void Row::copyFrom(const Row &other)
{
	setContent(other.content);
	setCnt(other.cnt);
	this->words = new char*[other.cnt];
	for (size_t i = 0; i < cnt; ++i)
	{
		if (!(words[i] = new(std::nothrow)char[strlen(other.words[i]) + 1]))
		{
			cleanMatrix(i);
			clean();
			throw std::bad_alloc();
		}
		strcpy(this->words[i], other.words[i]);
	}
}
void Row::cleanMatrix(size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete[]words[i];
	}
	delete[] words;
	words = nullptr;
}
void Row::clean()
{
	delete[]content;
	content = nullptr;
}

void Row::deserialize(std::fstream &file) 
{
	char temp[MAX_LEN + 1];
	file.getline(temp, MAX_LEN);
	setContent(temp);
	setCnt(cntWords(content));
	setWords(temp);
}

void Row::serialize(std::fstream&file)const
{
	file << content << '\n';
}

