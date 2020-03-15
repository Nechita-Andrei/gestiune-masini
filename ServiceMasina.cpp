#include "ServiceMasina.h"
#include <fstream>
#include <random>

std::vector<Car> ServiceCars::getAll()
{
	return repo.getAll();
}

int ServiceCars::size()
{
	return repo.size();
}

void ServiceCars::storeCar(const int& id, const std::string& producer, const std::string& model, const std::string& type)
{
	Car c{ id,producer,model,type };
	v.validateCar(c);
	undoList.push_back(repo);
	repo.push_back(c);
}

void ServiceCars::deleteCar(const int& id)
{
	Car c{ id,"","","" };
	undoList.push_back(repo);
	repo.erase(c);
}

void ServiceCars::updateCar(const int& id, const std::string& producer, const std::string& model, const std::string& type)
{
	Car c{ id,producer,model,type };
	v.validateCar(c);
	undoList.push_back(repo);
	repo.update(c);
}

Car ServiceCars::searchCar(const int& id)
{

	std::vector<Car> list = repo.getAll();
	std::vector<Car>::iterator it = std::find_if(list.begin(), list.end(), [id](const Car& c) {return c.getID() == id; });
	if (it == list.end()) {
		throw Exception{ "Invalid id.\n" };
	}
	return it[0];
}

std::vector<Car> ServiceCars::filterCar(const int& condition, const std::string& filter)
{
	std::vector<Car> list = repo.getAll();
	std::vector<Car> new_list(list.size());
	std::vector<Car>::iterator it;
	switch (condition) {
	case 0:
		it = std::copy_if(list.begin(), list.end(), new_list.begin(), [filter](const Car& c) {auto found = c.getProducer().find(filter); return found != std::string::npos; });
		break;
	case 1:
		it = std::copy_if(list.begin(), list.end(), new_list.begin(), [filter](const Car& c) {auto found = c.getModel().find(filter); return found != std::string::npos; });
		break;
	case 2:
		it = std::copy_if(list.begin(), list.end(), new_list.begin(), [filter](const Car& c) {auto found = c.getType().find(filter); return found != std::string::npos; });
		break;
	default:
		break;
	}
	new_list.resize(std::distance(new_list.begin(), it));
	return new_list;
}

std::vector<Car> ServiceCars::sortCars(const int& condition, const bool& reversed)
{
	std::vector<Car> list = repo.getAll();
	switch (condition) {
	case 0:
		/*Sort by id*/
		std::sort(list.begin(), list.end(), [](const Car& c1, const Car& c2) {return c1.getID() < c2.getID(); });
		break;
	case 1:
		std::sort(list.begin(), list.end(), [](const Car& c1, const Car& c2) {return c1.getProducer() < c2.getProducer(); });
		break;
	case 2:
		std::sort(list.begin(), list.end(), [](const Car& c1, const Car& c2) {return c1.getModel() < c2.getModel(); });
		break;
	case 3:
		std::sort(list.begin(), list.end(), [](const Car& c1, const Car& c2) {return c1.getType() < c2.getType(); });
		break;
	default:
		break;
	}
	if (reversed) {
		std::reverse(list.begin(), list.end());
	}
	return list;
}

ServiceCars::ServiceCars()
{
}

void ServiceCars::loadCars()
{
	repo.read("cars.txt");
}

void ServiceCars::saveCars()
{
	std::ofstream fout("cars.txt");
	std::vector<Car> list = repo.getAll();

	for (const auto& x : list) {
		fout << x.toString();
	}
}

void ServiceCars::generateCars(const int& nr) {
	char letters[] = "qwertyuiopasdfghjklzxcvbnm";
	int i = 0;
	while (i < nr) {
		int id = repo.size() + 1;
		std::string producer, model, type;
		while (producer.length() < 5) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, strlen(letters) - 1);
			int rndNr = dist(mt);// numar aleator intre [0,size-1]
			producer += letters[rndNr];
		}
		while (model.length() < 5) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, strlen(letters) - 1);
			int rndNr = dist(mt);// numar aleator intre [0,size-1]
			model += letters[rndNr];
		}
		while (type.length() < 5) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, strlen(letters) - 1);
			int rndNr = dist(mt);// numar aleator intre [0,size-1]
			type += letters[rndNr];
		}

		Car c{ id,producer,model,type };
		repo.push_back(c);
		i++;
	}
}

std::vector<Car> ServiceCars::getRandomCars(int& nr)
{
	if (nr = repo.size()) {
		nr = repo.size();

	}
	std::vector<Car> list;
	while (nr) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repo.size() - 1);
		int rndNr = dist(mt);// numar aleator intre [0,repo.size()-1]

		Car c = searchCar(rndNr);
		list.push_back(c);
		nr--;
	}
	return list;
}


void ServiceCars::doUndo()
{
	undo.doUndo(repo, undoList);
}

bool ServiceCars::canUndo() const
{
	return undoList.size() != 0;
}

ServiceCars::~ServiceCars()
{
}