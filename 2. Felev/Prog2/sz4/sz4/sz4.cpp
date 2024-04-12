// sz4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "iostream"
#include "string"
//#include "regex.h"

char myid[] = "Rittgasszer A'kos <ra1709@hszk.bme.hu> Z8WK8D\n";
char mytask[] = "Feladat = 6\n";

bool IsBigLetter(char ch)
{
	if ((int)ch >= 65 && (int)ch <= 90)
		return true;
	return false;
}

bool FitRegEx(std::string line)
{
	// _?(0)?[0-9]*W6.+[A-Z]*.*mmese(B|b)



	if (line.length() <= (int)11)
		return false;

	int idx = 0;
	if (line[idx] == '#') //[^#]
		return false;
	++idx;

	if (line[idx] == '_')
		++idx;
	if (line[idx] == '0')
		++idx;

	while (isdigit(line[idx]))
		++idx;

	if (line[idx] != 'W')
		return false;
	++idx;
	if (line[idx] != '6')
		return false;
	++idx;

	if (line[line.length() - 1] != 'B' && line[line.length() - 1] != 'b')
		return false;
	if (line[line.length() - 2] != 'e' || line[line.length() - 3] != 's')
		return false;
	if (line[line.length() - 4] != 'e' || line[line.length() - 5] != 'm' || line[line.length() - 6] != 'm')
		return false;

	if (line[idx] == '_')
		++idx;

	if (line[idx] == '0')
		++idx;

	if (IsBigLetter(line[idx]) && !IsBigLetter(line[idx + 1]))
		return false;
	++idx;

	if (IsBigLetter(line[idx + 1]))
	{
		return true;
	}

	if (idx + 1 < line.length() - 6)
		return true;


	return false;
}

int main()
{
	//setbuf(stdout, NULL);
	printf(myid);
	printf(mytask);

	std::string line;

	int countOfLines = 0;
	int countFitRegEx = 0;

	while (std::cin >> line)
	{
		if (FitRegEx(line))
		{
			++countFitRegEx;
			std::cerr << "OUT: " << line << "GOOD" << std::endl;
		}
		else
		{
			std::cerr << "OUT: " << line << "BAD" << std::endl;
		}
		++countOfLines;
	}

	//printf("%o/%\n", countOfLines, countFitRegEx);
	std::cout << countOfLines << '/' << countFitRegEx << std::endl;
    return 0;
}

