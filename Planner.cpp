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

std::string startClass = "zZvc";
std::string endClass = "cZvz";
std::string startHomework = "zZvh";
std::string endHomework = "hZvz";
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

void addHomework()
{
	if (!(data.size() > 0))
	{
		std::cout << "Please Add a Class First\n";
		system("pause");
		return;
	}
	showData(NUMBEREDCLASSES);
	std::cout << "\nEnter Class Number To Add Homework To:";
	int pickedClass;
	if(!cinNumber(pickedClass, data.size()))
	{
		return;
	}

	std::cout << "Enter Homework:";
	std::string homework;
	if (!cinString(homework))
	{
		return;
	}
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
	if (!cinString(newClass))
	{
		return;
	}
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
	std::string newName;
	if (!cinString(newName))
	{
		return;
	}
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

void resetAll()
{
	std::cout << "Are You Sure You Want to Clear All Data? [y,n]:";
	std::string removeOrNot;
	if (!cinString(removeOrNot))
	{
		return;
	}
	if (removeOrNot == "y" || removeOrNot == "y")
	{
		data.clear();
	}
	return;
}

void resetHomework()
{
	for (auto i = 0; i < data.size(); i++)
	{
		data[i].homework.clear();
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
				"[2] = Switch Class Order\n"
				"[3] = Reset Homeowrk\n"
				"[4] = Reset All Data\n\n"
				"Selection:";
			if (!cinNumber(settingsOption, 4))
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
			case 3:
				resetHomework();
				break;
			case 4:
				resetAll();
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