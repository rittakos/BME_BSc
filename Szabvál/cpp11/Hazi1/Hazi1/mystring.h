#ifndef MY_STRING_H
#define MY_STRING_H


#include <iostream>
#include "string.h"

class StringValue
{
	int ref;

	char* string_;
	int size_;

public:
	StringValue();
	StringValue(const char* str);

	StringValue(const StringValue& other) = delete;
	StringValue& operator= (const StringValue& other) = delete;
	~StringValue();

	int& getRefCount();
	int length() const;
	char* c_str() const;
	std::ostream& print(std::ostream& os);
};



class MyString
{
	StringValue* stringValue_;

public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator= (const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator= (MyString&& other) noexcept;
	~MyString() noexcept;

	int length() const;

	char operator[](int idx) const;
	char& operator[](int idx);

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend MyString operator+(const MyString str1, const MyString str2);
	friend MyString operator+(const MyString str1, const char);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

MyString operator+(const MyString str1, const MyString str2);
MyString operator+(const MyString str1, const char ch);

MyString operator+=(MyString& str1, const MyString str2);
MyString operator+=(MyString& str1, const char ch);



#endif
