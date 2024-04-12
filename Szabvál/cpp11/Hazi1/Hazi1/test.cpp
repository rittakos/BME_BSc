#include "mystring.h"


int main()
{
	MyString string1;
	MyString string2("alma");

	std::cout << string2 << "    " << string2.length() << std::endl; //alma    4
	std::cout << string2[3] << std::endl; //a


	std::cin >> string1;

	MyString string3 = string1 + string2;
	std::cout << string3 << std::endl; //"string1"alma

	MyString string4 = string2;
	MyString string5("korte");
	string5 += string2;
	std::cout << string5 << std::endl; //almaalma

	MyString string6 = string2 + '6';
	string6 += '7';
	std::cout << string6 << std::endl; //alma67
	
	MyString string7 = string6;

	string7[4] = '0';
	std::cout << string6 << std::endl; //alma67
	std::cout << string7 << std::endl; //alma07
}