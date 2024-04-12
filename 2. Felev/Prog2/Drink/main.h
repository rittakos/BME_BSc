//
// Created by akosr on 02/05/2019.
//

#ifndef DRINKS_MAIN_H
#define DRINKS_MAIN_H

#include "drink.h"
#include "array.hpp"
#include "ingredient.h"
#include <iostream>
#include <sstream>

void AddIngredient(Array<Ingredient>& ingredients)
{
    String name;
    std::cout << "Hozzavalo hozzaadasa:" << std::endl;
    std::cout << "Neve: ";
	std::cin >> name;
    std::cout << std::endl;
    Ingredient newIngredient(name, 0, "");

	ingredients.Add(newIngredient);
}

void AddAlcoholicDrink(Array<Drink*>& drinks, Array<Ingredient>& ingredients)
{
	String name;
	String description;

	std::cout << "Neve: ";
	std::cin >> name;
	std::cout << std::endl;

	std::cout << "Leiras: ";
	std::cin >> description;
	std::cout << std::endl;

	double alcoholPrecent;
	std::cout << "Alkoholtartalom szazalekban: ";
	std::cin >> alcoholPrecent;
	/*try
	{
		std::cin >> alcoholPrecent;
	}
	catch (...)
	{
		alcoholPrecent = 0;
	}*/
	std::cout << std::endl;

	AlkoholicDrink* newDrink = new AlkoholicDrink(name, description, alcoholPrecent);
	


	std::cout << "Hozzavalok (add meg azok sorszamat amelyikeket tartalmazza az ital, ha nincs tobb -1et): " << std::endl;
	std::cout << ingredients;
	int  ingredinetId;
	std::cin >> ingredinetId;
	std::cout << std::endl;


	double value;
	String type;

	while (ingredinetId != -1)
	{
		std::cout << "Add meg a hozzavalo mennyiseget: ";
		std::cin >> value;
		std::cout << "Add meg a hozzavalo mertekegyseget: ";
		std::cin >> type;

		ingredients[ingredinetId].SetAmount(value, type);

		newDrink->AddIngredient(ingredients[ingredinetId]);

		std::cout << std::endl << "Kovetkezo hozzavalo: ";
		std::cin >> ingredinetId;
	}

	drinks.Add(newDrink);
}

void AddNonAlcoholicDrink(Array<Drink*>& drinks, Array<Ingredient>& ingredients)
{
	String name;
	String description;

	std::cout << "Neve: ";
	std::cin >> name;
	std::cout << std::endl;

	std::cout << "Leiras: ";
	std::cin >> description;
	std::cout << std::endl;

	NonAlkoholicDrink* newDrink = new NonAlkoholicDrink(name, description);


	std::cout << "Hozzavalok (add meg azok sorszamat amelyikeket tartalmazza az ital, ha nincs tobb -1et): " << std::endl;
	std::cout << ingredients;
	int  ingredinetId;
	std::cin >> ingredinetId;
	std::cout << std::endl;

	


	double value;
	String type;

	while (ingredinetId != -1)
	{
		std::cout << "Add meg a hozzavalo mennyiseget: ";
		std::cin >> value;
		std::cout << "Add meg a hozzavalo mertekegyseget: ";
		std::cin >> type;

		ingredients[ingredinetId].SetAmount(value, type);

		newDrink->AddIngredient(ingredients[ingredinetId]);

		std::cout << std::endl << "Kovetkezo hozzavalo: ";
		std::cin >> ingredinetId;
	}

	drinks.Add(newDrink);
}

void AddDrink(Array<Drink*>& drinks, Array<Ingredient>& ingredients)
{
	std::cout << "Ital hozzaadasa:" << std::endl;
	char type;
	std::cout << "Alkoholos az ital? (Igen: i, Nem: n (mas karakter eseten alkoholos lesz)): ";
	std::cin >> type;
	std::cout << std::endl;

	if (type == 'n')
		AddNonAlcoholicDrink(drinks, ingredients);
	else
		AddAlcoholicDrink(drinks, ingredients);

	}

void Delete(Array<Drink*>& drinks)
{
	std::cout << drinks;
	std::cout << "Add meg annak az italnak a sorszamat amelyiket el szeretned tavolitani: ";

	size_t idx;
	std::cin >> idx;
	std::cout << std::endl;
	while (idx >= drinks.GetDataSize())
	{
		std::cout << "Hibás index!!! index: ";
		std::cin >> idx;
		std::cout << std::endl;
	}

	drinks.Remouve(drinks[idx]);
}

void Save(std::ofstream& file, const Array<Drink*>& drinks, const Array<Ingredient>& ingredients)
{
	file << ingredients.GetDataSize() << std::endl;
	for (size_t idx = 0; idx < ingredients.GetDataSize(); ++idx)
	{
		file << ingredients[idx].GetName() << std::endl;
	}
	file << drinks.GetDataSize() << std::endl;
	for (size_t idx = 0; idx < drinks.GetDataSize(); ++idx)
	{
		file << drinks[idx]->GetName() << std::endl;
		file << drinks[idx]->GetDescription() << std::endl;
		file << drinks[idx]->GetIngredients().GetDataSize() << std::endl;
		for (size_t id = 0; id < drinks[idx]->GetIngredients().GetDataSize(); ++id)
		{
			file << ingredients[idx].GetName() << "\t" << ingredients[idx].GetAmount().getValue() << "\t" << ingredients[idx].GetAmount().getType() << std::endl;
		}
	}
}

void ReadFile(std::ifstream& file, Array<Drink*>& drinks, Array<Ingredient>& ingredients)
{
	size_t numOfIngredients;
	size_t numOfDrinks;

	file >> numOfIngredients;
	for (size_t idx = 0; idx < numOfIngredients; ++idx)
	{
		String name;
		file >> name;
		Ingredient ingredient(name, 0, "");
		ingredients.Add(ingredient);
	}

	file >> numOfDrinks;
	for (size_t idx = 0; idx < numOfDrinks; ++idx)
	{
		String name;
		file >> name;
		String description;
		file >> description;
		size_t numOfContainedIngredients;

		Drink* currentDrink = new Drink(name, description);

		file >> numOfContainedIngredients;
		for (size_t id = 0; id < numOfContainedIngredients; ++id)
		{
			String n;
			file >> n;
			double value;
			file >> value;
			String type;
			file >> type;
			Ingredient currentIngredient(n, value, type);
			currentDrink->AddIngredient(currentIngredient);
		}
		drinks.Add(currentDrink);
	}
}

void List(std::ostream& os, const Array<Ingredient>& ingredients, const Array<Drink*>& drinks)
{
    os << "Hozzavalok:" << std::endl;

	for (size_t idx = 0; idx < ingredients.GetDataSize(); ++idx)
		os << ingredients[idx].GetName() << std::endl;
    
    /*for(size_t idx = 0; idx < ingredients.GetDataSize(); ++idx)
    {
        os << idx;
        ingredients[idx].operator<<(os) << std::endl;
        //os << ingredients[idx];
    }*/

    os << "Italreceptek:" << std::endl;

	for (size_t idx = 0; idx < drinks.GetDataSize(); ++idx)
		os << *drinks[idx];
    //os << drinks;

    /*for(size_t idx = 0; idx < ingredients.GetDataSize(); ++idx)
    {
        os << idx;
        drinks[idx].operator<<(os) << std::endl;
        //os << ingredients[idx];
    }*/
}
#endif //DRINKS_MAIN_H
