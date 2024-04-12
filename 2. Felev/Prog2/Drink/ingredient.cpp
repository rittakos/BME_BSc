//
// Created by akosr on 16/04/2019.
//

#include "ingredient.h"

Amount::Amount(Amount &other)
{
    this->value = other.value;
    this->type = other.type;
}

double Amount::getValue() const
{
    return this->value;
}

String Amount::getType() const
{
    return this->type;
}

std::ostream &operator<<(std::ostream &os, const Amount& amount)
{
    os<<amount.getValue()<<" "<<amount.getType();
    return os;
}

void Amount::operator>>(std::iostream &is)
{

}

Ingredient& Ingredient::operator=(const Ingredient &other)
{
    this->amount = other.GetAmount();
    this->name = other.GetName();
    return *this;
}

std::ostream &operator<<(std::ostream& os, const Ingredient& ingredient)
{
    os << ingredient.GetName();
    os << "\t";
    os << ingredient.GetAmount();
    return os;
}

void Ingredient::operator>>(std::istream &is)
{

}

Ingredient::Ingredient(Ingredient &other)
{
	this->name = other.GetName();
	this->amount = other.GetAmount();
}
