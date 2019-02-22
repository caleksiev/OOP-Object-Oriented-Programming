#ifndef READ_HEADER_INCLUDED
#define READ_HEADER_INCLUDED
#include "System.h"
#include"Result.h"
#include"ReaderTemp.h"
class Reader
{
public:
	Reader(const char*fileName);

	//всички функции връщат стрингово съобщение,указващо резултата от операцията
	const char*addTags(const char*com, char*des, const char*cont ,const char*linkDes=0,unsigned num=0);
	const char*addAttrib(size_t inedx,const char*name,const char*value);
	const char*save()const;
	const char*remove(const char*des);
	const char*moveTo(size_t index, const char*des);
	void print(std::ostream&os)const;
public:
	size_t getLastPostIndex()const;

private:
	//търси тага по дадено описание и връща неговия индекс ако го намери,в противен случай -1
	int findDes(const char*des)const;

	Result checkFileStatus(const char*fileName)const;

	//по време на четенето от файла се записват в стринг всички атрибути на дадения таг
	//и след създаването на самия таг,атрибутите се добавят към него
	//разчитаме,че атрибутите са коректни -> Име="Стойност"
	//ако даден атрибут не се разпознае се прескача
	void addAttrib(char*attrib);
private:
	//по даден файл прочита всчики тагове от нeго,предполага че файловете са с валиден синтаксис
	//за успешно прочитане от файла трябва всеки таг също така да е заграден от <p>...</p>
	//за различните видове тагове функцията използва долните 4
	Result readFromFile(const char*fileName);
private:
	Result readPar(std::fstream&f, char*ptrCnt, char*descr, char*content, char*attrib,size_t pos);
	Result readHed(std::fstream&f, char*ptrCnt, char*descr, char*content, char*attrib,size_t pos);
	Result readVideoImag(std::fstream&f, char*ptrCnt, char*descr, char*content, char*attrib, char*type,size_t pos);
	Result readLink(std::fstream&f, char*ptrCnt, char*descr, char*content, char*attrib, char*linkDes, size_t pos);
private:
	Reader(const Reader&other) = delete;
	Reader operator=(const Reader&other) = delete;
private:
	System system;
};
#endif
