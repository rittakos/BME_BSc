#include <string>
#include <iostream>

class Immutable
{
private:

	const int number;
	const std::string text;

public:

	Immutable(int number, std::string text) : number{number}, text{text} {}

	int			getNumber	()	const	{ return number; }
	std::string getText		()	const	{ return text; }

	Immutable update(int number, std::string text) const
	{
		if (number == this->number && text == this->text)
			return *this;
		return Immutable(number, text);
	}

	Immutable update(int number) const
	{
		if (number == this->number)
			return *this;
		return Immutable(number, text);
	}

	Immutable update(std::string text) const
	{
		if (text == this->text)
			return *this;
		return Immutable(number, text);
	}
};

int main()
{
	Immutable i1(0, "");
	std::cout << "i1: number: " << i1.getNumber() << "\t text: " << i1.getText() << std::endl;
	Immutable i2 = i1.update(4);
	std::cout << "i2: number: " << i2.getNumber() << "\t text: " << i2.getText() << std::endl;
	Immutable i3 = i2.update("alma");
	std::cout << "i3: number: " << i3.getNumber() << "\t text: " << i3.getText() << std::endl;

}