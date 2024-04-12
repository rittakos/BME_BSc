//
// Created by akosr on 16/04/2019.
//

#ifndef DRINKS_DRINK_H
#define DRINKS_DRINK_H

#include "ingredient.h"
#include "array.hpp"
#include "string5.h"

class Drink
{
    String name;
    String description;
    Array<Ingredient> ingredients;
public:
	Drink(): name(""), description("")
	{

	}
    Drink(const String& n, const String& d);
    Drink (Drink& other);
	virtual ~Drink()
	{

	}

    const String& GetName() const {return this->name;}
    const String& GetDescription() const {return this->description;}
    const Array<Ingredient>& GetIngredients() const {return this->ingredients;}

	void SetName(const String& n) 
	{
		this->name = n; 
	}
	void SetDescription(const String& description)
	{
		this->description = description;
	}


    void AddIngredient(Ingredient& ingredient);

	bool operator==(const Drink& other)
	{
		if (this->name == other.GetName() && this->description == other.GetDescription() && this->ingredients == other.GetIngredients())
			return true;
		return false;
	}

    void operator>> (std::iostream& is);
};

std::ostream& operator<<(std::ostream& os, const Drink&);

class AlkoholicDrink : public Drink
{
    double alcoholPrecent;
public:
    AlkoholicDrink(const String& n, const String& d, const double alcoholPrecent);
    double getAlcoholPrecent() const;
	void SetAlcoholPrecent(const double& alcoholPrecent)
	{
		this->alcoholPrecent = alcoholPrecent;
	}
	~AlkoholicDrink() 
	{

	}
};

class NonAlkoholicDrink : public Drink
{
public:
    NonAlkoholicDrink (const String& n, const String& d);
	~NonAlkoholicDrink()
	{

	}
};

#endif //DRINKS_DRINK_H
