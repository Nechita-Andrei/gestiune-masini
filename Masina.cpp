#include "Masina.h"
Car::Car()
{
}

std::string Car::toString()const
{
	return std::to_string(id) + "  " + producer + "  " + model + "  " + type + "\n";
}

std::string Car::toString1() const
{
	return std::to_string(id) + "," + producer + "," + model + "," + type + "\n";
}
std::string Car::toString2() const
{
	return producer + " " + model;
}
Car::~Car()
{
}



void ValidationCars::validateCar(const Car& c)
{
	std::string errors = "";
	if (c.getID() < 1)
		errors += "Invalid ID.\n";
	if (c.getProducer() == "")
		errors += "Invalid Producer.\n";
	if (c.getModel() == "")
		errors += "Invalid Model.\n";
	if (c.getType() == "")
		errors += "Invalid Type.\n";

	if (errors != "")
		throw Exception{ errors };
}

ValidationCars::ValidationCars()
{
}


ValidationCars::~ValidationCars()
{
}
