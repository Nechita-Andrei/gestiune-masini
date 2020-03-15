#pragma once
#include "RepoMasina.h"
#include "Masina.h"
#include "Undo.h"
#include <algorithm>

class ServiceCars
{
private:
	RepositoryCars repo;
	ValidationCars v;
	std::vector<RepositoryCars> undoList;
	UndoAction undo;
	/*
	UndoAdd undoAdd;
	UndoDelete undoDelete;
	UndoUpdate undoUpdate;
	*/
public:

	ServiceCars();
	ServiceCars(const RepositoryCars& repo, const ValidationCars& v) :repo{ repo }, v{ v }{};
	ServiceCars(const ServiceCars& s) :repo{ s.repo }, v{ s.v }{};

	/*Load the cars from a file*/
	void loadCars();
	/*Save the cars to a file*/
	void saveCars();

	/*Return the list of cars.*/
	std::vector<Car> getAll();
	/*Return the size of the list of cars.*/
	int size();
	/*Store a new car in the repo. Raise error if there is another car with the same id.*/
	void storeCar(const int& id, const std::string& producer, const std::string& model, const std::string& type);
	/*Delete the car with a specific id.*/
	void deleteCar(const int& id);
	/*Update the car producer, model and type for a specific id.*/
	void updateCar(const int& id, const std::string& producer, const std::string& model, const std::string& type);
	/*Search for the element with a specific id*/
	Car searchCar(const int& id);
	/*Filter the elements by producer/model/type*/
	std::vector<Car> filterCar(const int& condition, const std::string& filter);
	/*Sort cars by id/producer/model/type. Can be reversed.*/
	std::vector<Car> sortCars(const int& condition, const bool& reversed);

	/*Generate a fixed number of cars*/
	void generateCars(const int& nr);

	/*Get some random cars from memory*/
	std::vector<Car> getRandomCars(int& nr);

	/*Undo the last command*/
	void doUndo();

	/*Verify if the undo operation can be done*/
	bool canUndo()const;

	~ServiceCars();
};

