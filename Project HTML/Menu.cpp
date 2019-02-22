#include"Menu.h"

void skipRest()
{
	std::cin.ignore(1000, '\n');
	std::cin.clear();
}
void skipSpaces()
{
	char s = std::cin.get();
	while (s == ' ')
		s = std::cin.get();
	std::cin.unget();
}


void Menu()
{
	char command[MAX_COMM_LEN];
	char filePath[MAX_FILE_LEN];

	bool exit = true;
	while (exit)
	{
		try
		{
			std::cout << "$:";
			std::cin >> command;
			if (!strcmp(command, "load"))
			{
				std::cin >> filePath;
				skipRest();
				Reader r(filePath);
				std::cout << "The file is seccsesfully loaded!\n";
				Menu1(&exit, r);
			}
			else if (!strcmp(command, "exit"))
			{
				std::cout << "You exit the program!\n";
				break;
			}
			else if (!strcmp(command, "add") || !strcmp(command, "remove") || !strcmp(command, "print")
				|| !strcmp(command, "save") || !strcmp(command, "moveTo"))
			{
				std::cout << "You must firts load a file!\n";
				skipRest();
			}
			else
			{
				std::cout << "Unknown command!\n";
				skipRest();
			}
		}
		catch (const std::invalid_argument&os)
		{
			std::cout << os.what();
		}
		catch (const char*s)
		{
			std::cout << s;
		}
	}

}

void Menu1(bool* exit, Reader& r)
{
	char command[MAX_COMM_LEN];
	char type[MAX_COMM_LEN];
	size_t size;
	//char attrib[1024];
	char des[MAX_CONTENT];
	char cont[MAX_CONTENT];
	char linkDes[MAX_CONTENT];

	while (true)
	{
		std::cout << "$:";
		std::cin >> command;
		if (!strcmp(command, "add"))
		{
			std::cin >> type;
			if (!strcmp(type, "heading") || !strcmp(type, "text") || !strcmp(type, "video")
				|| !strcmp(type, "link") || !strcmp(type, "image"))
			{
				if (!strcmp(type, "heading"))
				{
					std::cin >> size;
					if (!std::cin)
					{
						std::cout << "You must enter a size for heading!\n";
						std::cin.clear();
						skipRest();
						continue;
					}
				}
				std::cin >> des;
				if (!strcmp(type, "link"))
				{
					std::cin >> cont;
					skipSpaces();
					std::cin.getline(linkDes, MAX_CONTENT);
				}
				else
				{
					skipSpaces();
					std::cin.getline(cont, MAX_CONTENT);
				}
				try
				{
					std::cout << r.addTags(type, des, cont, linkDes, size);
				}
				catch (const std::invalid_argument&ex)
				{
					std::cout << ex.what();
					continue;
				}
				std::cout << "Do you want to add atributes to this tag.Press + add or press other key to refuse!:";
				char s;
				std::cin >> s;
				skipRest();
				if (s == '+')
				{
					size_t index = r.getLastPostIndex();
					attribMenu(type, index, r);
					std::cin.unget();
					skipRest();
				}
			}
			else
			{
				std::cout << "Unkown command!\n";
				skipRest();
			}
		}
		else if (!strcmp(command, "save"))
		{
			std::cout << r.save();
			skipRest();
			break;
		}
		else if (!strcmp(command, "load"))
		{
			std::cout << "You have to save firts the current file before to proceed to the other one!\n";
			skipRest();
		}
		else if (!strcmp(command, "remove"))
		{
			std::cin >> des;
			std::cout << r.remove(des);
			skipRest();
		}
		else if (!strcmp(command, "moveTo"))
		{
			std::cin >> size;
			if (!std::cin)
			{
				std::cout << "Wrong commad!\n";
				std::cin.clear();
				skipRest();
				continue;
			}
			std::cin >> des;
			try
			{
				std::cout << r.moveTo(size, des);
			}
			catch (const std::out_of_range&ex)
			{
				std::cout << ex.what();
			}
			skipRest();
		}
		else if (!strcmp(command, "print"))
		{
			r.print(std::cout);
			skipRest();
		}
		else if (!strcmp(command, "exit"))
		{
			*exit = false;
			std::cout << r.save();
			std::cout << "You exit the program!\n";
			break;
		}
		else
		{
			std::cout << "Unkown command!\n";
			skipRest();
		}
	}
}

void attribMenu(const char * type,size_t index,Reader&r)
{
	char s = ' ';
	char text[MAX_CONTENT];
	bool arr[3];
	arr[0] = false; arr[1] = false; arr[2] = false;

	if (!strcmp(type, "heading") || !strcmp(type,"video"))
	{
		std::cout << "At the moment  system not support any attributes for heading and for video!\n";
		return;
	}
	if (!strcmp(type, "image"))
	{
		std::cout << "The supported attributes for image are:\n"
			<< "to choose the attrib enter his digit,press x to cancel the option!\n"
			<< "1)alt\n"
			<< "2)width\n"
			<< "3)height\n";
		while (!arr[0] || !arr[1] || !arr[2])
		{	
			std::cout << "Enter num or x to escape:";
			std::cin >> s;
			skipRest();
			//std::cin.get();
			switch (s)
			{
			case '1':
				if (arr[0])
				{
					std::cout << "Already set!\n";
					break;
					//C:\\Users\PC\\Desktop\\pictore.jpg
				}
				std::cout << "Enter the text!\n$:";
				std::cin.getline(text, MAX_CONTENT, '\n');
				std::cout << r.addAttrib(index, "alt", text);
				arr[0] = true;
				break;
			case '2':
				if (arr[1])
				{
					std::cout << "Already set!\n";
					break;
				}
				std::cout << "Enter the size!\n$:";
				std::cin >> text;
				std::cout << r.addAttrib(index, "width", text);
				arr[1] = true;
				break;
			case '3':
				if (arr[2])
				{
					std::cout << "Already set!\n";
					break;
				}
				std::cout << "Enter the size!\n$:";
				std::cin >> text;
				std::cout << r.addAttrib(index, "height", text);
				arr[2] = true;
				break;
			case 'x':
				arr[0] = true; arr[1] = true; arr[2] = true;
				std::cout << "You close the attribute option!\n";
				break;
			default:
				std::cout << "INVALID TYPE!\n";
			}
		}
	}
	if (!strcmp(type, "text"))
	{
		std::cout << "The supported attributes for text are:\n"
			<< "to choose the attrib enter his digit,press other button to cancel the option!You can only choose one!\n"
			<< "1)align-left\n"
			<< "2)align-center\n"
			<< "3)align-rigth\n";
		std::cout << "Enter num or other button to escape:";
		std::cin >> s;
		skipRest();
		switch (s)
		{
		case '1':
			std::cout << r.addAttrib(index, "align", "left");
			break;
		case '2':
			std::cout << r.addAttrib(index, "align", "center");
			break;
		case '3':
			std::cout << r.addAttrib(index, "align", "right");
		default:
			std::cout << "You close the attribute option!\n";
		}
	}

	if (!strcmp(type, "link"))
	{
		std::cout << "The supported attribute for image at the moment is -title \n";
		std::cout << "Do you want to add it?(+ or press other to close):";
		std::cin >> s;
		skipRest();
		if (s == '+')
		{
			std::cout << "Enter the extra content:";
			std::cin.getline(text, MAX_CONTENT, '\n');
			std::cout << r.addAttrib(index, "title", text);
		}
	}
}
