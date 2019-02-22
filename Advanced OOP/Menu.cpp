#include"Menu.h"
void skipSpaces()
{
	char s = std::cin.get();
	while (s == ' ')
		s = std::cin.get();
	std::cin.unget();
}

void signalWrong()
{
	std::cin.unget();
	std::cout << "WRONG COMMAND!\n";
	std::cin.ignore(1000 , '\n');
	std::cin.clear();
}

//не съм се погрижил особено добре за неправилния вход и по точно като се въведе по-дълъг стринг
//ама самото изплозване на getline ми е малко тегаво и затова повечето прочитания са със cin
void Menu()
{
	//ще се съхраняват съответните команди
	char actorName[MAXLEN_NAME];
	char sbjName[MAXLEN_NAME];
	char post[MAXLEN_POST];
	char content[MAXLEN_CONTENT];
	char des[MAXLEN_CONTENT];
	char command[MAXLEN_COMMAND];
	size_t num;
	while (true)
	{
		std::cout << "$:";
		std::cin >> actorName;
		if (!strcmp(actorName, "quit"))
		{
			std::cout << "You quit the program!\n";
			break;
		}
		if (!strcmp(actorName, "info"))
		{
			Validation::getInstance().infoCommand(std::cout);
		}
		else
		{
			std::cin >> command;
			if (!strcmp(command, "rename"))
			{
				std::cin >> sbjName;
				std::cout << Validation::getInstance().renameCommand(actorName, sbjName);
			}
			else if (!strcmp(command, "add_moderator") || !strcmp(command, "add_user"))
			{
				std::cin >> sbjName;
				std::cin >> num;
				if (!std::cin)
					signalWrong();
				else
					std::cout << Validation::getInstance().addUsersCommand(actorName, command, sbjName, num);
			}
			else if (!strcmp(command, "block"))
			{
				std::cin >> sbjName;
				std::cout << Validation::getInstance().blockUnblockCommand(actorName, sbjName, 1);
			}
			else if (!strcmp(command, "unblock"))
			{
				std::cin >> sbjName;
				std::cout << Validation::getInstance().blockUnblockCommand(actorName, sbjName, 0);
			}
			else if (!strcmp(command, "remove_user"))
			{
				std::cin >> sbjName;
				std::cout << Validation::getInstance().removeUsersCommand(actorName, sbjName);
			}
			else if (!strcmp(command, "post"))
			{
				std::cin >> post;
				if (!strcmp(post, "[image]"))
				{
					skipSpaces();
					std::cin.getline(content, MAXLEN_CONTENT);
					std::cout << Validation::getInstance().addPostCommand(actorName, post, content);
				}
				else if (!strcmp(post, "[text]"))
				{
					skipSpaces();
					std::cin.getline(content, MAXLEN_CONTENT);
					std::cout << Validation::getInstance().addPostCommand(actorName, post, content);
				}
				else if (!strcmp(post, "[url]"))
				{
					skipSpaces();
					std::cin.getline(content, MAXLEN_CONTENT, ' ');
					std::cin.getline(des, MAXLEN_CONTENT);
					std::cout << Validation::getInstance().addPostCommand(actorName, post, content, des);
				}
				else
					signalWrong();
			}
			else if (!strcmp(command, "remove_post"))
			{
				std::cin >> num;
				if (!std::cin)
					signalWrong();
				else
					std::cout << Validation::getInstance().removePostCommand(actorName, num);
			}
			else if (!strcmp(command, "view_all_posts"))
			{
				std::cin >> sbjName;
				std::cout << Validation::getInstance().makeHTMLallCommand(actorName, sbjName);
			}
			else if (!strcmp(command, "view_post"))
			{
				std::cin >> num;
				if (!std::cin)
					signalWrong();
				else
					std::cout << Validation::getInstance().makeHTMLCommand(actorName, num);
			}
			else
				signalWrong();
		}
		//ако има нещо останало в потока го прескачаме
		std::cin.unget();
		std::cin.ignore(1000, '\n');
		std::cin.clear();
	}
}