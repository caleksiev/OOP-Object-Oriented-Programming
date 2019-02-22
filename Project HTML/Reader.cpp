#include "Reader.h"

const size_t MAXLEN = 500;
const size_t MAX_ROW_LEN = 1024;
Reader::Reader(const char * fileName):system(fileName)
{
	Result res = checkFileStatus(fileName);
	switch (res)
	{
	case WRONG_FILE_PATH:
		throw std::invalid_argument("WRONG FILE PATH!\n");
	case FILE_MUST_BE_HTML:
		throw std::invalid_argument("FILE MUST BE A HTML!\n");
	case NEW_FILE_CREATED://файлът не същесвува и е създаде
		break;
	case FILE_EXIST://файлът съществува следва прочитане на информацията
		Result res = readFromFile(fileName);
		switch (res)
		{
		case FILE_PROBLEM_READ:
		case FILE_NOT_OPEN:
			throw "Problem while operating with file!\n";
			break;
		case NO_DESCR_IN_FILE:
			throw "";//to do:
		case UKNOWN_FILE_DATA:
			throw "The data is unkown,the tag is not supported or is not enclosed by <p>....</p>\n";
		default:
			;//всичко е успешно приключило
		}
	}
}
const char * Reader::addTags(const char*com, char*des, const char*cont, const char*linkDes, unsigned num)
{
	system.addTags(com, des, cont, linkDes, num);
	return TAG_ADDED;
}

const char * Reader::addAttrib(size_t index, const char * name, const char*value)
{
	system.addAtt(index, name, value);
	return ATTR_ADDED;
}
const char * Reader::save() const
{
	if (system.saveData())
		return FILE_SAVED;

	return FILE_NOT_SAVED;

}

const char * Reader::remove(const char * des)
{
	size_t index = findDes(des);
	if (index == -1)
		return TAG_NOT_FOUND;
	system.removeTag(index);
	return TAG_REMOVED;
}

const char * Reader::moveTo(size_t pos, const char * des)
{
	size_t index = findDes(des);
	if (index == -1)
		return TAG_NOT_FOUND;
	system.moveTo(index, pos);
	return TAG_MOVED;
}

void Reader::print(std::ostream & os) const
{
	os << "Information about tags:\n";
	size_t size = system.getSize();
	if (!size)
		os << "No tags at the moment!\n";
	for (size_t i = 0; i < size; ++i)
		os << i << ":"<<system.getType(i)<<" with "<< "desc: " << system.getDes(i) << "\n";
}

size_t Reader::getLastPostIndex() const
{
	return system.getSize() - 1;
}

int Reader::findDes(const char * des) const
{
	size_t size = system.getSize();
	for (size_t i = 0; i < size; ++i)
	{
		if (!strcmp(system.getDes(i), des))
			return i;
	}
	return -1;
}

Result Reader::checkFileStatus(const char * fileName) const
{
	size_t size = strlen(fileName);
	if (fileName[size - 1] != 'l' || fileName[size - 2] != 'm' || fileName[size - 3] != 't' || fileName[size - 4] != 'h')
		return FILE_MUST_BE_HTML;
	std::fstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open())//ако файла не същестува се опитваме да го създаде
	{
		f.close();
		f.open(fileName, std::ios::out);
		if (!f.is_open())//подадения път е грешен
			return WRONG_FILE_PATH;
		return NEW_FILE_CREATED;
	}
	return FILE_EXIST;
}


Result Reader::readPar(std::fstream&f,char*ptrCnt,char*descr,char*content,char*attrib, size_t pos)
{
	char temp[MAXLEN];
	skipUnletter(ptrCnt);//прескачаме докато не стигнем до съответния таг
	copyText(ptrCnt, temp);

	if (!strcmp(temp, "p"))
	{
		skipUnletter(ptrCnt);
		copyText(ptrCnt, temp);
		if (!strcmp(temp, "descr"))
		{
			skipUnletter(ptrCnt);
			copyText(ptrCnt, descr);//записваме описанието

			skipUnletter(ptrCnt);
			copyText1(ptrCnt, attrib);//засипсваме атрибутите,които ще бъдат обработени по-късно
			////////
			skipSpace(f);//ако има някакви whitespace или newLine ги прескачаме
			f.getline(content, MAXLEN, '<');//прочитаме съдържанието
			//прескачаме затварящия таг,премаме че го има защото по условие файлът е с валиден синтаксис
			f.getline(temp, MAXLEN, '>');
			if (!f)
				return FILE_PROBLEM_READ;
			//няма проблем с четеното и имаме нужната информация за създаване на тага
			system.addTags("text", descr, content);
			//остава да прочетем атрибутите
			addAttrib(attrib);
		}
		else
		{
			std::cout << "On tag " << pos << " the description is not found!\n";
			return NO_DESCR_IN_FILE;
		}
	}
	else
	{
		std::cout << "On tag " << pos << " this was unrecognizable:" << temp<<"\n";
		return UKNOWN_FILE_DATA;
	}
	return SUCCSEES_FILE_READ;
}

Result Reader::readHed(std::fstream & f, char * ptrCnt, char * descr, char * content, char * attrib, size_t pos)
{
	char temp[MAXLEN];
	unsigned short size = *ptrCnt - '0';//прочитаме размера на заглавието

	skipUnletter(ptrCnt);
	copyText(ptrCnt, temp);
	if (!strcmp(temp, "descr"))
	{
		skipUnletter(ptrCnt);
		copyText(ptrCnt, descr);//записваме описанието

		skipUnletter(ptrCnt);
		copyText1(ptrCnt, attrib);//записваме атрибутите
		////////
		skipSpace(f);
		f.getline(content, MAXLEN, '<');//записваме и съдържанието
		//прескачаме затварящия таг за заглавие и за параграф,премаме че го има защото по условие файлът е с валиден синтаксис
		f.getline(temp, MAXLEN, '>');
		f.getline(temp, MAXLEN, '>');
		if (!f)
			return FILE_PROBLEM_READ;
		//няма проблем с четеното и имаме нужната информация за създаване на тага
		system.addTags("heading", descr, content, "", size);
		//остава да прочетем атрибутите
		addAttrib(attrib);
	}
	else
	{
		std::cout << "On tag " << pos << " the description is not found!\n";
		return NO_DESCR_IN_FILE;
	}

	return SUCCSEES_FILE_READ;

}

Result Reader::readVideoImag(std::fstream & f, char * ptrCnt, char * descr, char * content, char * attrib,char*type, size_t pos)
{
	char temp[MAXLEN];

	skipUnletter(ptrCnt);
	copyText(ptrCnt, temp);

	if (!strcmp(temp, "src"))
	{
		skipUnletter(ptrCnt);
		copyTextLink(ptrCnt, content);//прочитаме първо съдържанието

		skipUnletter(ptrCnt);
		copyText(ptrCnt, temp);
		if (!strcmp(temp, "descr"))
		{
			skipUnletter(ptrCnt);
			copyText(ptrCnt, descr);//прочитаме описанието

			skipUnletter(ptrCnt);
			copyText1(ptrCnt, attrib);//и атрибутите
			if (!strcmp(type, "iframe"))
			{
				//прескачаме 2та затварящи тага за параграфа и видеото
				f.getline(temp, MAXLEN, '>');
				f.getline(temp, MAXLEN, '>');
				if (!f)
					return FILE_PROBLEM_READ;
				system.addTags("video", descr, content);
			}
			else
			{
				//няма затварящ таг,прескачаме само затварящия таг за параграфа
				f.getline(temp, MAXLEN, '>');
				if (!f)
					return FILE_PROBLEM_READ;
				system.addTags("image", descr, content);
			}
			//остава да прочетем атрибутите
			addAttrib(attrib);
		}
		else
		{
			std::cout << "On tag " << pos << " the description is not found!\n";
			return NO_DESCR_IN_FILE;
		}
	}
	else
	{
		std::cout << "On tag " << pos << " this was unrecognizable:"<<"\n" << temp;
		return UKNOWN_FILE_DATA;
	}
	return SUCCSEES_FILE_READ;
}

Result Reader::readLink(std::fstream & f, char * ptrCnt, char * descr, char * content, char * attrib, char * linkDes, size_t pos)
{
	char temp[MAXLEN];

	skipUnletter(ptrCnt);
	copyText(ptrCnt, temp);

	if (!strcmp(temp, "href"))
	{
		skipUnletter(ptrCnt);
		copyTextLink(ptrCnt, content);//прочитаме първо съдържанието

		skipUnletter(ptrCnt);
		copyText(ptrCnt, temp);
		if (!strcmp(temp, "descr"))
		{
			skipUnletter(ptrCnt);
			copyText(ptrCnt, descr);//прочитаме описанието

			skipUnletter(ptrCnt);
			copyText1(ptrCnt, attrib);//и атрибутите


			skipSpace(f);
			f.getline(linkDes, MAXLEN, '<');

			//прескачаме 2та затварящи тага за параграфа и линка
			f.getline(temp, MAXLEN, '>');
			f.getline(temp, MAXLEN, '>');
			if (!f)
				return FILE_PROBLEM_READ;
			system.addTags("link", descr, content, linkDes);

			//остава да прочетем атрибутите
			addAttrib(attrib);
		}
		else
		{
			std::cout << "On tag " << pos << " the description is not found!\n";
			return NO_DESCR_IN_FILE;
		}
	}
	else
	{
		std::cout << "On tag " << pos << " this was unrecognizable:" << "\n" << temp;
		return UKNOWN_FILE_DATA;
	}
	return SUCCSEES_FILE_READ;
}

//////////////
void Reader::addAttrib( char * attrib)
{
	//приемаме че синтаксиса на атрибутите е валиден Име="Стойност"
	//ако даден таг не се разпознаве то го прескачаме
	char name[MAXLEN];
	char value[MAXLEN];

	while (*attrib)
	{
		skipUnletter(attrib);
		copyText(attrib, name);//прочитаме името

		skipUnletter(attrib);
		copyText2(attrib, value);//прочитаме стойността
		if (isAtribb(name))//ако разпознаем атрибута го създаваме
		{
			size_t index = getLastPostIndex();
			system.addAtt(index, name, value);
		}
	}
}
Result Reader::readFromFile(const char*fileName)
{
	char mainCont[MAXLEN];
	char descr[MAXLEN];
	char attrib[MAXLEN];
	char content[MAXLEN];
	char type[MAXLEN];
	char linkDes[MAXLEN];

	std::fstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open())
		return FILE_NOT_OPEN;
	for (size_t i=0;f.good();++i)
	{
		skipSpace(f);
		f.getline(mainCont, MAXLEN, '>');
		char*ptrCnt = mainCont;
		if (!f)//възниква fail проверяваме дали не сме стигнали края на файла
		{
			f.clear();
			f.getline(mainCont, MAXLEN);//ако не успее значи сме стигнали на края
			if (!f)
				continue;
			else
				return FILE_PROBLEM_READ;
		}
		if (isMetaData(mainCont))//ако ни е познатата мета данната ок
			--i;
		else if (!strcmp(mainCont, "<p"))//тагът ще е един от 4те без параграф
		{
			f.getline(mainCont, MAXLEN, '>');
			if (!f)
				continue;
			skipUnletter(ptrCnt);
			copyText(ptrCnt, type);
			if (!strcmp(type, "h"))
			{
				Result res= readHed(f, ptrCnt, descr, content, attrib,i);
				if (res != SUCCSEES_FILE_READ)
					return res;
			}
			else if (!strcmp(type, "iframe") || !strcmp(type, "img"))
			{
				Result res = readVideoImag(f, ptrCnt, descr, content, attrib, type,i);
				if (res != SUCCSEES_FILE_READ)
					return res;
			}
			else if (!strcmp(type, "a"))
			{
				Result res = readLink(f, ptrCnt, descr, content, attrib, linkDes, i);
				if (res != SUCCSEES_FILE_READ)
					return res;
			}
			else
			{
				std::cout << "On tag " << i << " this was unrecognizable:" << type << "\n";
				return UKNOWN_FILE_DATA;
			}
		}
		else//би трябвало тагът да е параграф
		{
			Result res= readPar(f, ptrCnt, descr, content, attrib,i);
			if (res != SUCCSEES_FILE_READ)
				return res;
		}
	}
	if (f.eof())
		return SUCCSEES_FILE_READ;
	else
		return FILE_PROBLEM_READ;
}