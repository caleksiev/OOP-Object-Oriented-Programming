#include"Text.h"
const unsigned int MAXLEN_FPATH = 100;
const unsigned int MAXLEN_COMMAND = 12;

void ValidatingInput(char*filepath)
{
	bool OK = false;
	do
	{
		std::cout << "Enter a filepath!\n";
		std::cin >> filepath;
		try
		{
			Text temp(filepath);
			OK = true;
		}
		catch (const char*what)
		{
			std::cout << what << "\n";
			if (strcmp(what, "Unvalid file path!"))
				throw;
		}
	} while (!OK);
}
bool CheckStreamGood()
{
	if (!std::cin)
	{
		std::cin.ignore(100, '\n');
		std::cin.clear();
		return false;
	}
	return true;
}
//C:\\Users\\PC\\Desktop\\Homework2.2\\Project1\\Project1\\111.txt
int main()
{
	try
	{
		char filepath[MAXLEN_FPATH];
		ValidatingInput(filepath);
		//the file path is correct
		Text text(filepath);
		std::cout << "You are ready to make transformation to your file!\n";
		char command[MAXLEN_COMMAND];
		while (true)
		{
			std::cout << "Enter command!\n";
			std::cin >> command;
			if (!strcmp(command, "makeHeading"))
			{
				size_t line;
				std::cin >> line;
				if (CheckStreamGood())
					text.MakeHeading(line);
			}
			else if (!strcmp(command, "makeItalic"))
			{
				size_t line, from, to;
				std::cin >> line >> from >> to;
				if (CheckStreamGood())
					text.MakeItalic(line, from, to);
			}
			else if (!strcmp(command, "makeBold"))
			{
				size_t line, from, to;
				std::cin >> line >> from >> to;
				if (CheckStreamGood())
					text.MakeBold(line, from, to);
			}
			else if (!strcmp(command, "makeCombine"))
			{
				size_t line, from, to;
				std::cin >> line >> from >> to;
				if (CheckStreamGood())
					text.MakeCombine(line, from, to);
			}
			else if (!strcmp(command, "addLine"))
			{
				char x = std::cin.get();
				while (x == ' ')
					x = std::cin.get();
				std::cin.unget();

				char line[MAX_LEN + 1];
				std::cin.getline(line, MAXLEN_FPATH);
				text.AddLine(line);
			}
			else if (!strcmp(command, "remove"))
			{
				size_t line;
				std::cin >> line;
				if (CheckStreamGood())
					text.Remove(line);
			}
			else if (!strcmp(command, "quit"))
			{
				if (CheckStreamGood())
					text.SaveToNewFormat();
				std::cout << "You quit the program!\n";
				break;
			}
			else
			{
				std::cin.ignore(100, '\n');
				std::cin.clear();
				std::cout << "UNKNOWN COMMAND!\n";
			}
		}
	}
	catch (const char*what)
	{
		std::cout << what;
	}
	catch (const std::bad_alloc&)
	{
		std::cout << "No enough memmory!\n";
	}
	catch (...)
	{
		std::cout << "Unknown error!\n";
	}

	system("pause");
	return 0;
}