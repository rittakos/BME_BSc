//
// Created by akosr on 16/04/2019.
//

#include "drink.h"

Drink::Drink(const String& n, const String& d) : name(n), description(d)
{

}

NonAlkoholicDrink::NonAlkoholicDrink(const String& n, const String& d) : Drink(n, d)
{

}

AlkoholicDrink::AlkoholicDrink(const String& n, const String& d, const double alcoholPrecent) : Drink::Drink(n, d), alcoholPrecent(alcoholPrecent)
{

}

Drink::Drink(Drink &)
{

}

void Drink::AddIngredient(Ingredient& ingredient)
{
    this->ingredients.Add(ingredient);
}

std::ostream &operator<<(std::ostream &os, const Drink& drink)
{
    os << drink.GetName() << std::endl;
    os << drink.GetDescription() << std::endl;
    os << drink.GetIngredients();
    os << std::endl;
    //os << this->ingredients << std::endl;
    return os;
}

void Drink::operator>>(std::iostream &/*is*/)
{

}

double AlkoholicDrink::getAlcoholPrecent() const
{
    return this->alcoholPrecent;
}

