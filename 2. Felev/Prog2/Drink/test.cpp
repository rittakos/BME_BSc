//
// Created by akosr on 24/04/2019.
//
#include "test.h"
#include "array.hpp"
#include "drink.h"
#include "ingredient.h"
#include "string5.h"
#include <iostream>

void test1()
{
    Array<Drink> drinks(1);
    Array<Ingredient> ingredients(1);

    Ingredient viz("viz", 0, "");
    ingredients.Add(viz);

    Ingredient cukor("cukor", 0, "");
    ingredients.Add(cukor);

    Drink limonade("limonade", "Keverd ossze a vizet cukorral meg citrommal");
    limonade.AddIngredient(viz);

    std::cout << limonade;

}
