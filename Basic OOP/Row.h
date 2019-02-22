#ifndef _ROW_HEADER_INCLUDED_
#define _ROW_HEADER_INCLUDED_
#include<fstream>
#include<iostream>
#include<cstring>
const unsigned int MAX_LEN = 1024;

class Row
{
	friend class Text;//пряко е свързан с класа,нека да има достъп до всичко от него 
public:
	Row();
	Row(const char*content);
	Row(const Row&other);
	Row& operator =(const Row&other);
	~Row();

private:
	//setters
	void setContent(const char*content);
	void setCnt(size_t cnt);
	void setWords(const char*content);
	void setNewWord(const char*word, size_t index);
	//getters
	const char*getContent()const { return content; }
	const char*getWord(size_t index)const { return words[index]; }
	size_t getCnt()const { return cnt; }

	//temp functions
	size_t cntWords(const char*)const;
	void copyFrom(const Row&other);
	void cleanMatrix(size_t size);
	void clean();

	//the main function that write and read on file the object
	void deserialize(std::fstream&file);
	void serialize(std::fstream&file)const;

private:
	char*content;//thec current sentence
	char**words;//every word from the sentence
	size_t cnt;//number of sentences
};
#endif