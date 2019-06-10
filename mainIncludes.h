#pragma once
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

extern std::vector<classAndHomework> data;