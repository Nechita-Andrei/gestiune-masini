#pragma once
#include<string>
using std::string;
class Car
{
private:
	int id;
	string producer;
	string model;
	string type;
public:
	Car(const int& id, const string& producer, const string& model, const string& type) :id{ id }, producer{ producer }, model{ model }, type{ type }{};
	Car(const Car& ot) :id{ ot.id }, producer{ ot.producer }, model{ ot.model }, type{ ot.type }{};
	Car();


	int getID() const { return id; }
	string getProducer() const { return producer; }
	string getModel() const { return model; }
	string getType() const { return type; }

	void setID(const int& id1) { id = id1; }
	void setProducer(const string& new_string) { producer = new_string; }
	void setModel(const string& new_string) { model = new_string; }
	void setType(const string& new_string) { type = new_string; }


	std::string toString() const;
	std::string toString1() const;
	std::string toString2()const;


	~Car();
};

class Exception {
private:
	string message;
public:
	Exception(string msg) :message{ msg } {};
	string getMessage() { return message; }
};

class ValidationCars
{

public:
	void validateCar(const Car& c);
	ValidationCars();
	~ValidationCars();
};

