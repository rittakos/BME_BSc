#include "stdafx.h"

#include "f_10.h"


#include <iostream>             
#include <cstring>

F10::F10()
{
	this->len = 0;
	this->line = new char[1];
	line[0] = 0;
}

F10::F10(const F10& other)
{
	len = other.len;
	line = other.line;
}

F10& F10::operator=(const F10& other)
{
	len = other.len;
	line = other.line;
	return *this;
}

F10::~F10()
{

}


const char* F10::ident() const
{
	return "Rittgasszer A'kos <ra1709@hszk.bme.hu> Z8WK8D";
}

// megallapitjja, hogy a parameterkent kapot sztringben megtalalhato-e valamelyik
// karaktersorozat az alabbiakbol:
//    alapja
//    dolgoznia
//    ugyanazok


bool F10::match(const char *line)
{
	bool containe = false;

	const char* alapja = "alapja";
	const char* dolgoznia = "dolgoznia";
	const char* ugyanazok = "ugyanazok";

	int charId = 0;
	char ch = line[charId];



	while (ch != 0)
	{
		if (ch == 'a')
		{
			int idx = 0;
			for (idx = charId + 1; idx < charId + 6; ++idx)
			{
				if (line[idx] == alapja[idx - (charId)])
					containe = true;
				else
				{
					containe = false;
					break;
				}

			}
			if (idx == charId + 6)
				break;
		}
		else if (ch == 'd')
		{
			int idx;
			for (idx = charId + 1; idx < charId + 9; ++idx)
			{
				if (line[idx] == dolgoznia[idx - (charId)])
					containe = true;
				else
				{
					containe = false;
					break;
				}
			}
			if (idx == charId + 9)
				break;
		}
		else if (ch == 'u')
		{
			int idx;
			for (idx = charId + 1; idx < charId + 9; ++idx)
			{
				if (line[idx] == ugyanazok[idx - (charId)])
					containe = true;
				else
				{
					containe = false;
					break;
				}
			}
			if (idx == charId + 9)
				break;
		}

		++charId;
		ch = line[charId];
	}
	if (containe)
	{
		delete[] this->line;
		this->line = new char[charId + 1];
		strcpy_s(this->line, strlen(line) + 1, line);
		//strcpy(this->line, line);
		return true;
	}
	return false;
}
// visszaadja annak a szringnek a cimet melyben utoljara a match egyezest talalt

const char* F10::getLine() const
{
	return this->line;
}
