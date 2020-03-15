#include "Gestiune_masini.h"
#include <QtWidgets/QApplication>
#include "ServiceMasina.h"
#include "RepoMasina.h"
#include "GUI.h"
#include "Test.h"
#include <iostream>
using namespace std;

void addSomeCars(ServiceCars& s) {
	s.storeCar(1, "Mazda", "3", "Sport");
	s.storeCar(2, "Mazda", "6", "Sedan");
	s.storeCar(3, "Honda", "Civic", "Sport");
	s.storeCar(4, "Audi", "A3", "Sport");
	s.storeCar(5, "BMW", "S7", "Confort");
	s.storeCar(6, "Suzuki", "Jimny", "SUV");
}

int main(int argc, char *argv[])
{
	Test t;
	t.testAll();
	
	
	ValidationCars v;
	RepositoryCars r;
	ServiceCars s{ r,v };
	s.generateCars(20);
	QApplication a(argc, argv);
	a.setApplicationName("Cars Service");
	GUI gui{ s };
	gui.show();


	return a.exec();
}
