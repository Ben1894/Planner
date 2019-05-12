// Planner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

std::vector<std::vector<std::string>> data;
std::vector<std::string> classes;


//getline(ifs, str);
//std::string option;
//std::cin >> option;
//Start of Classes
//End of Classes Line
//load into 2d vector memory and print over current file every timed
//Start of Print     //replace the first 
//End of Print      


/*
normal.push_back(std::vector<int>());
myvector.erase(myvector.begin() + 5);
myvector.erase(myvector.begin(), myvector.begin() + 3)
myvector.push_back(i);
myVector[i].erase(myVector[i].begin() + columnToDelete);
if (myVector[i].size() > columnToDelete)
*/
void displayClasses();

void storeToVector()
{
}
void updateText()
{
}
void displayHomework()
{
	for (int i = 0; i < classes.size(); i++)
	{
		std::cout << classes[0] << "\n";
		for (int j = 0; j < data[j].size(); j++)
		{
			std::cout << "   " << data[i][j] << "\n";
		}
	}
}
void addHomework()
{
	int pickedClass;
	std::string homework;
	displayClasses();
	std::cout << "\nEnter Class Number To Add Homework To:";
	std::cin >> pickedClass;
	std::cout << "\nEnter Homework:";
	std::cin >> homework;
	data[(pickedClass-1)].push_back(homework);
}
void removeHomework()
{

}
void addClass()
{
	std::string newClass;
	std::cin >> newClass;
	data.push_back(std::vector<std::string>());
	classes.push_back(newClass);	
}
void openSettings()
{
}

void displayClasses()      //remember to subtract 1 from classes though
{
	for (int i = 0; i < classes.size(); i++)
	{
		std::cout << i+1 << ".";
		std::cout << classes[i] << " ";
	}
}

//std::vector<std::vector<int>> data;
//data.resize(1, std::vector<std::string>(2, "HI"));


int main()
{
	while (1)
	{
		//scroll through and print everything with c
		int no_of_cols = 5;
		int no_of_rows = 10;
		int initial_value = 0;

		std::vector<std::vector<std::string>> matrix;
		matrix.resize(no_of_rows, std::vector<std::string>(no_of_cols, "Hi"));

		// Read from matrix.
		std::string value = matrix[1][2];

		// Save to matrix.
		matrix[3][1] = 5;
		std::string d;
		std::cout << "What Pick Operation to Preform:\n";
		std::cout <<
			"[1] = Display Homework\n"
			"[2] = Add Homework\n"
			"[3] = Remove Homework\n"
			"[4] = Add Class\n"
			"[5] = Open Settings\n";
		short option;
		std::cin >> option;

		switch (option)
		{
		case 1:
			displayHomework();
			break;
		case 2:
			addHomework();
			break;
		case 3:
			removeHomework();
			break;
		case 4:
			addClass();
			break;
		case 5:
			openSettings();
			break;
		default:
			std::cout << "Please Enter a Valid Number";
			break;
		}
	}
    return 0; 
}
