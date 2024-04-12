#include "mystring.h"


StringValue::StringValue()
{
	//std::cout << "--StringValue Constructror()" << std::endl;
	string_ = new char[1];
	size_ = 1;
	ref = 1;
	string_[0] = '\0';
}

StringValue::StringValue(const char* str)
{
	//std::cout << "--StringValue Constructor(char*)" << std::endl;
	size_ = strlen(str) + 1;
	string_ = new char[size_];
	ref = 1;
	strcpy(string_, str);
}

StringValue::~StringValue()
{
	//std::cout << "--StringValue Destructror" << std::endl;
	delete[] string_;
}


int& StringValue::getRefCount()
{
	return ref;
}

char* StringValue::c_str() const
{
	return string_;
}

int StringValue::length() const
{
	return size_;
}

std::ostream& StringValue::print(std::ostream& os)
{
	os << string_;
	return os;
}






MyString::MyString()
{
	//std::cout << "--MyString Constructor()" << std::endl;
	stringValue_ = new StringValue();
}

MyString::MyString(const char* str)
{
	//std::cout << "--MyString Constructor(char*)" << std::endl;
	stringValue_ = new StringValue(str);
}


MyString::MyString(const MyString& other)
{
	//std::cout << "--MyString copy constructor" << std::endl;
	this->stringValue_ = other.stringValue_;
	++stringValue_->getRefCount();
}

MyString& MyString::operator= (const MyString& other) 
{
	//std::cout << "--MyString operator=" << std::endl;
	if (this != &other)
	{
		delete stringValue_;
		this->stringValue_ = other.stringValue_;
		++stringValue_->getRefCount();
	}
	return *this;
}

MyString::MyString(MyString&& other) noexcept
{
	stringValue_ = other.stringValue_;
	other.stringValue_ = nullptr;
}

MyString& MyString::operator= (MyString&& other) noexcept
{
	if (this != &other)
	{
		if (stringValue_->getRefCount() == 1)
			delete stringValue_;
		else
			--stringValue_->getRefCount();

		this->stringValue_ = other.stringValue_;
		other.stringValue_ = nullptr;
	}
	return *this;
}

MyString::~MyString() noexcept
{
	//std::cout << "--MyString Destructror" << std::endl;
	if (stringValue_ != nullptr)
	{
		--stringValue_->getRefCount();
		if (stringValue_->getRefCount() == 0)
			delete stringValue_;
	}
	else
		delete stringValue_;
}

int MyString::length() const
{
	return stringValue_->length() - 1;
}


char MyString::operator[](int idx) const
{
	if (idx >= 0 && idx < this->length())
		return stringValue_->c_str()[idx];
	else
		throw std::runtime_error("index out of range");
}

char& MyString::operator[](int idx)
{
	MyString newString(stringValue_->c_str());
	if (stringValue_->getRefCount() == 1)
		delete stringValue_;
	else
		--stringValue_->getRefCount();

	this->stringValue_ = newString.stringValue_;
	newString.stringValue_ = nullptr;

	if (idx >= 0 && idx < this->length())
		return stringValue_->c_str()[idx];
	else
		throw std::runtime_error("index out of range");
}


std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	str.stringValue_->print(os);
	return os;
}
std::istream& operator>>(std::istream& is, MyString& str)
{
	MyString line("");

	char c;
	is.get(c);
	while (c != '\n') 
	{
		line += c;
		is.get(c);
	}

	str = line;

	return is;
}


MyString operator+(MyString str1, const MyString str2)
{
	char* str = new char[str1.length() + str2.length() + 1];
	strcpy(str, str1.stringValue_->c_str());
	strcat(str, str2.stringValue_->c_str());

	MyString res(str);
	delete[] str;

	return res;
}
MyString operator+(MyString str1, const char ch)
{
	char* str = new char[str1.length() + 2];
	strcpy(str, str1.stringValue_->c_str());
	strncat(str, &ch, 1);

	MyString res(str);
	delete[] str;

	return res;
}


MyString operator+=(MyString& str1, const MyString str2)
{
	str1 = str1 + str2;
	return str1;
}
MyString operator+=(MyString& str1, const char ch) 
{
	str1 = str1 + ch;
	return str1;
}