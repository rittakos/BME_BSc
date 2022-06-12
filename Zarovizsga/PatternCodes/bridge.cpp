#include <iostream>
#include <memory>

struct GearBox {
	virtual ~GearBox() = default;
	virtual void handleGear() = 0;
};

struct ManualGear : public GearBox {
	void handleGear() final {
		std::cout << "Manual gear\n";
	}
};

struct AutoGear : public GearBox {
	void handleGear() final {
		std::cout << "Auto gear\n";
	}
};

class Vehicle {
    private:
		std::unique_ptr<GearBox> gear;
    public:
		Vehicle(std::unique_ptr<GearBox> &&gear) : gear{ std::move(gear) }
		{}

		virtual ~Vehicle() = default;

		void shiftGear() {
			gear->handleGear();
		}
};

class Car : public Vehicle {
    public:
		using Vehicle::Vehicle;
};


int main() {

	auto mgear = std::make_unique<ManualGear>();
	auto agear = std::make_unique<AutoGear>();

	auto vehicle1 = std::make_unique<Car>(std::move(mgear));
	auto vehicle2 = std::make_unique<Car>(std::move(agear));

	vehicle1->shiftGear();
	vehicle2->shiftGear();
}
