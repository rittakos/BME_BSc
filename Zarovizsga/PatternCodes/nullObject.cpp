#include <iostream>
#include <memory>

class Animal
{
public:
	virtual void makeNoise() const = 0;
};

class Dog : public Animal
{
public:
	virtual void makeNoise() const override
	{
		std::cout << "Vau!" << std::endl;
	}
};

class NullAnimal : public Animal
{
public:
	virtual void makeNoise() const override final {}
};

enum class AnimalType{Dog, NoAnimal};

std::unique_ptr<Animal> createAnimal(AnimalType animalType = AnimalType::NoAnimal)
{
	switch (animalType)
	{
	case AnimalType::Dog:
		return std::make_unique<Dog>();
	default:
		return std::make_unique<NullAnimal>();
	}
	
}

int main()
{
	std::unique_ptr<Animal> animal = createAnimal(/*AnimalType::Dog*/);
	animal->makeNoise();
}