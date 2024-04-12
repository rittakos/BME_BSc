#include <iostream>
#include <fstream>

#include "memtrace.h"

#include "array.hpp"
#include "drink.h"
#include "main.h"



int main()	 {
    //test1();
	//Array<char*> string;
	//char ch = 'a';
	//string.Add(&ch);
	//Drink newDrink();

    Array<Ingredient> ingredients(1);
    Array<Drink*> drinks(1);

	std::ifstream load;
	load.open("drinks.txt");
	ReadFile(load, drinks, ingredients);
	load.close();



    std::cout<<"ITALRECEPTEK"<<std::endl<<std::endl;

    std::cout<<"MENU:   "<<"Hozzaado Hozzaadas: h, Recept Hozzaadas: r, Eltavolitas: e, Listazas: l, Kilepes: k" << std::endl;
    char command;
    std::cin >> command;
    while(command != 'k')
    {
        switch (command)
        {
            case 'h':
                AddIngredient(ingredients);
                break;
            case 'r':
                AddDrink(drinks, ingredients);
                break;
            case 'e':
                Delete(drinks);
                break;
            case 'l':
                List(std::cout, ingredients, drinks);
                break;
            default:
                std::cout << "Hibas parancs" << std::endl;
        }
		std::cout << "Kovetkezo parancs: ";
        std::cin >> command;

    }

	std::ofstream save;
	save.open("drinks.txt");
	Save(save, drinks, ingredients);
    save.close();
	for (size_t idx = 0; idx < drinks.GetDataSize(); ++idx)
	{
		delete drinks[idx];
	}
    return 0;
}
