// Planner.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <sstream>

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

std::string startClass = "zZvc";
std::string endClass = "cZvz";
std::string startHomework = "zZvh";
std::string endHomework = "hZvz";

enum displayOption
{
	NUMBEREDCLASSES,
	ENERYTHING,
	NUMBEREDHOMEWORK
};

bool cinInputValidation();
bool cinNumber(int &var, int numberCheck = -10);
int showData(displayOption option);

class classAndHomework
{
public:
	std::string name;
	std::vector<std::string> homework;
};

std::vector<classAndHomework> data;

void storeToVector()
{
	std::ifstream file("saveData.txt");
	std::string temp;
	std::getline(file, temp);
	file.close();
	if (temp == "")
	{
		return;
	}
	std::size_t findClassB = temp.find(startClass);
	std::size_t findHomeworkB = temp.find(startHomework);
	std::size_t findClassE = temp.find(endClass);
	std::size_t findHomeworkE = temp.find(endHomework);
	while (findClassB != -1)
	{
		if ((findHomeworkB < findClassE) && (findHomeworkB != -1))
		{
			std::string classToAdd = temp.substr(findClassB+startClass.size(), (findHomeworkB - findClassB)-endHomework.size());
			data.push_back(classAndHomework{classToAdd});
			while (findHomeworkE < findClassE)
			{
				std::string homeworkToAdd = temp.substr(findHomeworkB+startClass.size(), (findHomeworkE - findHomeworkB)-endHomework.size());
				data[data.size()-1].homework.push_back(homeworkToAdd);
				findHomeworkB = temp.find(startHomework,findHomeworkE);
				findHomeworkE = temp.find(endHomework, findHomeworkB);
			}
		}
		else
		{
			std::string classToAdd = temp.substr(findClassB+startClass.size(), (findClassE - findClassB) - endClass.size());  
			data.push_back(classAndHomework{classToAdd});
		}
		findClassB = temp.find(startClass, findClassE);
		findClassE = temp.find(endClass, findClassB);
	}

	
}
void updateTextFile()
{
	std::ofstream testing;
	testing.open("saveData.txt");
	for (auto i = 0; i < data.size(); i++)
	{
		testing << startClass << data[i].name;
		for (auto j = 0; j < data[i].homework.size(); j++)
		{
			testing << startHomework << data[i].homework[j] << endHomework;
		}
		testing << endClass;
	}
	testing.close();
}
void displayHomework()
{
	system("CLS");
	if (data.size() == 0)
	{
		std::cout << "Nothing to Display\n";
		system("pause");
		return;
	}
	showData(ENERYTHING);
	std::cout << "\n\n";
	system("pause");
	system("CLS");
}

int showData(displayOption option)
{
	int number = 1;
	for (auto i = 0; i < data.size(); i++)
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
	return number;
}


void addHomework()
{
	if (!(data.size() > 0))
	{
		std::cout << "Please Add a Class First\n";
		system("pause");
		return;
	}
	int pickedClass = 0;
	showData(NUMBEREDCLASSES);
	std::cout << "\nEnter Class Number To Add Homework To:";
	if(!cinNumber(pickedClass, data.size()))
	{
		return;
	}
	std::cout << "Enter Homework:";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string homework;
	std::getline(std::cin, homework);
	if (homework == "c") return;
	data[(pickedClass - 1)].homework.push_back(homework);
}

void removeHomework()
{
	int number = showData(NUMBEREDHOMEWORK);
	if (number == 1)
	{
		std::cout << "Please Add Homework First\n";
		system("pause");
		return;
	}
	std::cout << "Enter Homework Number to Remove:";
	int removeNumber = 0;
	number = 0;
	if (!cinNumber(removeNumber))
	{
		return;
	}
	removeNumber--;
	for (auto i = 0; i < data.size(); i++)
	{
		std::cout << data[i].name << "\n";
		for (auto j = 0; j < data[i].homework.size(); j++)
		{
			if (removeNumber == number)
			{
				data[i].homework.erase(data[i].homework.begin() + j);
			}
			number++;
		}
	}
}
void addClass()
{
	std::cout << "Enter Class Name:";
	std::string newClass;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, newClass);
	if (newClass == "c") return;
	data.push_back(classAndHomework{newClass});
}

void removeClass()
{
	if (data.size() == 0)
	{
		std::cout << "Please Enter a Class First\n";
		system("pause");
		return;
	}
	showData(NUMBEREDCLASSES);
	std::cout << "\nEnter Class Number to Remove:";
	int classNumber;
	if (!cinNumber(classNumber, data.size()))
	{
		return;
	}
	
	classNumber--;
	data.erase(data.begin() + classNumber);
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

void renameClass()
{
	if (!(data.size() > 0))
	{
		std::cout << "Please Add a Class First\n";
		system("pause");
		return;
	}
	int pickedClass = 0;

	showData(NUMBEREDCLASSES);
	std::cout << "\nEnter Class Number To Rename:";
	if (!cinNumber(pickedClass, data.size()))
	{
		return;
	}
	std::cout << "Enter New Name:";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string newName;
	std::getline(std::cin, newName);
	if (newName == "c") return;
	data[pickedClass-1].name = newName;
}

void switchClass()
{
	if (!(data.size() > 1))
	{
		std::cout << "Please Add 2 Classes First\n";
		system("pause");
		return;
	}
	int pickedClass = 0;
	int pickedClass2 = 0;
	showData(NUMBEREDCLASSES);
	std::cout << "\nEnter Class Number To Swap:";
	if (!cinNumber(pickedClass, data.size()))
	{
		return;
	}
	std::cout << "Enter Class Number To Swap Class With:";
	if (!cinNumber(pickedClass2, data.size()))
	{
		return;
	}
	std::swap(data[pickedClass - 1], data[pickedClass2 - 1]);
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
int main()
{
	storeToVector();
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 450, 460, TRUE);
	removeScrollbars();
	std::cout << "To Break from a Function Enter 'c'\n" << "or an Invalid Input\n\n";
	while (1)
	{
		removeScrollbars();
		std::cout << "Select Operation to Preform:\n";
		std::cout <<
			"[1] = Display Homework\n"
			"[2] = Add Homework\n"
			"[3] = Remove Homework\n"
			"[4] = Add Class\n"
			"[5] = Remove Class\n"
			"[6] = Settings\n\n"
			"Selection:";
		int option = 0;
		int settingsOption = 0;
		if (!cinNumber(option, 6))
		{
			option = -1;
		}
		removeScrollbars();
		system("CLS");
		switch (option)
		{
		case 1:
			displayHomework();
			break;
		case 2:
			addHomework();
			updateTextFile();
			break;
		case 3:
			removeHomework();
			updateTextFile();
			break;
		case 4:
			addClass();
			updateTextFile();
			break;
		case 5:
			removeClass();
			updateTextFile();
			break;
		case 6:
			std::cout << "Select Operation to Preform:\n";
			std::cout <<
				"[1] = Rename Class\n"
				"[2] = Switch Class Order\n\n"
				"Selection:";
			if (!cinNumber(settingsOption, 2))
			{
				settingsOption = -1;
			}
			system("CLS");
			switch (settingsOption)
			{
			case 1:
				renameClass();
				break;
			case 2:
				switchClass();
				break;
			default:
				break;
			}
			updateTextFile();
			break;
		default:
			break;
		}
		system("CLS");
	}
    return 0; 
}