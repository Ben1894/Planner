#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
# endif
# ifndef VC_EXTRALEAN
#   define VC_EXTRALEAN
# endif
# ifndef NOMINMAX
#   define NOMINMAX
# endif
#include <windows.h>
#include "mainIncludes.h"
#include "coreFunctions.h"

bool cinString(std::string &str, bool errorChecking)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, str);
	if (errorChecking == true)
	{
		if (str == "c")
		{
			return false;
		}
	}
	return true;
}

bool cinNumber(int &var, int numberCheck)
{
	std::cin >> var;
	if (!cinInputValidation())
	{
		system("CLS");
		std::cout << "Please Enter a Valid Input\n";
		system("pause");
		return false;
	}
	if (numberCheck < -9)
	{
		return true;
	}
	else
	{
		if (var > numberCheck)
		{
			system("CLS");
			std::cout << "Please Enter a Valid Selection\n";
			system("pause");
			return false;
		}
	}
	return true;
}

bool cinInputValidation()
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

int showData(displayOption option)
{
	int number = 1;
	for(auto i = 0; i < data.size(); i++)
	{
		if(option == NUMBEREDCLASSESWITHHOMEWORK)
		{
			if(data[i].homework.size() != 0)
			{
				std::cout << number << ".";
				std::cout << data[i].name << "\n";
				number++;
				for (auto j = 0; j < data[i].homework.size(); j++)
				{
					std::cout << "   ";
					std::cout << data[i].homework[j] << "\n";
				}
			}
		}
		else
		{
			if (option == NUMBEREDCLASSES)
			{
				std::cout << i + 1 << ".";
			}
			std::cout << data[i].name << "\n";
			if (option != NUMBEREDCLASSES)
			{
				for (auto j = 0; j < data[i].homework.size(); j++)
				{
					std::cout << "   ";
					if (option == NUMBEREDHOMEWORK)
					{
						std::cout << number << ".";
					}
					std::cout << data[i].homework[j] << "\n";
					number++;
				}
			}
		}
	}
	return number;
}

void removeScrollbars()
{
	try {
		HANDLE console2 = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(console2, &csbi);
		COORD scrollbar = {
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};

		if (console2 == 0) {
			throw 0;
		}
		else {
			SetConsoleScreenBufferSize(console2, scrollbar);
		}
	}
	catch (...) {
		std::cout << "Error removing scrollbar";
	}
}