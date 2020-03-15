#pragma once
#include <string>
#include <assert.h>
#include "ServiceMasina.h"
#include "Masina.h"
class Test
{
private:
	std::string msgError1 = "The element already exists.\n";
	std::string msgError2 = "The element doesn't exists\n";
public:

	void testCreateCar();
	void testValidateCar();

	void testStoreCar();
	void testDeleteCar();
	void testUpdateCar();
	void testSearchCar();
	void testFilterCars();
	void testSortCars();


	void testAll();

	Test();
	~Test();
};
