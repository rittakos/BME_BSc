//
// Created by akosr on 16/04/2019.
//

#ifndef DRINKS_INGREDIENT_H
#define DRINKS_INGREDIENT_H

#include "string5.h"

class Amount
{
    double value;
    String type;
public:
    Amount():value(0), type(""){}
    Amount(const double& v, const String& t) :value(v), type(t){}
    Amount(Amount& other);

    double getValue() const;

    String getType() const;

	void SetValue(const double& v) { this->value = v; }
	void SetType(const String& t) { this->type = t; }

    void operator>> (std::iostream& is);

    bool operator==(const Amount& other) const
    {
        if(this->type == other.type && this->value == other.value)
            return true;
        return false;
    }
};

std::ostream& operator<< (std::ostream& os, const Amount& amount);


class Ingredient
{
    String name;
    Amount amount;
public:
    explicit Ingredient(const String& n = "", double value = 0, const String& type = "") :name(n), amount(value, type){}

    Ingredient(Ingredient& other);

    Ingredient& operator= (const Ingredient& other);

    const String GetName() const {return this->name;}
    const Amount& GetAmount() const {return this->amount;}

	void SetAmount(const double& value, const String& type)
	{
		this->amount.SetValue(value);
		this->amount.SetType(type);
	}

    void operator>>(std::istream& is);
    bool operator== (const Ingredient& other) const
    {
        if(this->amount == other.amount && this->name == other.name)
            return true;
        return false;
    }
};

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient);

#endif //DRINKS_INGREDIENT_H
