#include "Test.h"
void Test::testCreateCar()
{
	Car c{ 1,"abc","bcc","cba" };
	assert(c.getID() == 1);
	assert(c.getProducer() == "abc");
	assert(c.getModel() == "bcc");
	assert(c.getType() == "cba");

	c.setID(2);
	c.setProducer("aaa");
	c.setModel("bbb");
	c.setType("ccc");

	assert(c.toString() == "2  aaa  bbb  ccc\n");
}

void Test::testValidateCar()
{
	ValidationCars v;
	Car c_good{ 1,"abc","bcc","cba" };
	Car c_bad{ -3,"","","" };

	try {
		v.validateCar(c_good);
		v.validateCar(c_bad);
	}
	catch (Exception & e) {
		assert(e.getMessage() == "Invalid ID.\nInvalid Producer.\nInvalid Model.\nInvalid Type.\n");
	}
}

void Test::testStoreCar()
{
	RepositoryCars r;
	ValidationCars v;
	ServiceCars s{ r,v };
	int id = 1;
	std::string producer = "abc";
	std::string model = "bcc";
	std::string type = "nasjd";

	s.storeCar(id, producer, model, type);
	try {
		s.storeCar(id, producer, model, type);
	}
	catch (Exception & e) {
		assert(e.getMessage() == msgError1);
	}

}

void Test::testDeleteCar()
{
	RepositoryCars r;
	ValidationCars v;
	ServiceCars s{ r,v };
	int id = 1;
	std::string producer = "abc";
	std::string model = "bcc";
	std::string type = "nasjd";

	s.storeCar(id, producer, model, type);
	assert(s.size() == 1);

	s.deleteCar(1);
	assert(s.size() == 0);

	s.storeCar(1, "Mazda", "3", "Hatchback");
	s.storeCar(2, "Mazda", "3", "Sedan");
	s.storeCar(3, "Mazda", "6", "Sedan");
	s.storeCar(4, "Honda", "Civic", "Hatchback");
	s.storeCar(5, "Toyota", "Yaris", "Hatchback");
	s.storeCar(6, "Toyota", "Auris", "Sedan");
	try {
		s.deleteCar(4);
		s.deleteCar(4);
	}
	catch (Exception & e) {
		assert(e.getMessage() == msgError2);
	}
}

void Test::testUpdateCar()
{
	RepositoryCars r;
	ValidationCars v;
	ServiceCars s{ r,v };
	int id = 1;
	std::string producer = "abc";
	std::string model = "bcc";
	std::string type = "nasjd";

	s.storeCar(id, producer, model, type);

	producer = "aaa";
	model = "bbb";
	type = "ccc";

	s.updateCar(id, producer, model, type);
	std::vector<Car> list = s.getAll();
	assert(list[0].getID() == 1);
	assert(list[0].getProducer() == producer);
	assert(list[0].getModel() == model);
	assert(list[0].getType() == type);

	try {
		s.updateCar(2, producer, model, type);
	}
	catch (Exception & e) {
		assert(e.getMessage() == msgError2);
	}

}

void Test::testSearchCar()
{
	ServiceCars s;
	s.storeCar(1, "aaa", "bbb", "ccc");
	try {
		Car c = s.searchCar(1);
		assert(c.getProducer() == "aaa");
		c = s.searchCar(1000);
	}
	catch (Exception & e) {
		assert(e.getMessage() == "Invalid id.\n");
	}

}

void Test::testFilterCars()
{
	ServiceCars s;
	s.storeCar(1, "Mazda", "3", "Hatchback");
	s.storeCar(2, "Mazda", "3", "Sedan");
	s.storeCar(3, "Mazda", "6", "Sedan");
	s.storeCar(4, "Honda", "Civic", "Hatchback");
	s.storeCar(5, "Toyota", "Yaris", "Hatchback");
	s.storeCar(6, "Toyota", "Auris", "Sedan");

	std::vector<Car> list = s.filterCar(0, "Mazda");
	assert(list.size() == 3);

	list = s.filterCar(1, "3");
	assert(list.size() == 2);

	list = s.filterCar(2, "Sedan");
	assert(list.size() == 3);

	list = s.filterCar(2, "4x4");
	assert(list.size() == 0);
}

void Test::testSortCars()
{
	ServiceCars s;
	s.storeCar(1, "Mazda", "3", "Hatchback");
	s.storeCar(2, "Mazda", "3", "Sedan");
	s.storeCar(3, "Mazda", "6", "Sedan");
	s.storeCar(4, "Honda", "Civic", "Hatchback");
	s.storeCar(5, "Toyota", "Yaris", "Hatchback");
	s.storeCar(6, "Toyota", "Auris", "Sedan");

	std::vector<Car> list = s.sortCars(0, false);
	assert(list[0].getID() == 1);
	assert(list[list.size() - 1].getID() == 6);

	list = s.sortCars(0, true);
	assert(list[0].getID() == 6);
	assert(list[list.size() - 1].getID() == 1);

	list = s.sortCars(1, false);
	assert(list[0].getID() == 4);
	assert(list[list.size() - 1].getID() == 6);

	list = s.sortCars(1, true);
	assert(list[0].getID() == 6);
	assert(list[list.size() - 1].getID() == 4);

	list = s.sortCars(2, false);
	assert(list[0].getID() == 1);
	assert(list[list.size() - 1].getID() == 5);

	list = s.sortCars(2, true);
	assert(list[0].getID() == 5);
	assert(list[list.size() - 1].getID() == 1);

	list = s.sortCars(3, false);
	assert(list[0].getID() == 1);
	assert(list[list.size() - 1].getID() == 6);

	list = s.sortCars(0, true);
	assert(list[0].getID() == 6);
	assert(list[list.size() - 1].getID() == 1);

}



void Test::testAll()
{
	testCreateCar();
	testValidateCar();
	testStoreCar();
	testDeleteCar();
	testUpdateCar();
	testSearchCar();
	testFilterCars();
	testSortCars();
}



Test::Test()
{
}


Test::~Test()
{
}