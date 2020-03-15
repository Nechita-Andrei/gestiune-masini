#pragma once
#include "Masina.h"
#include <vector>
#include <string>

typedef Car ElementT;
class RepositoryCars
{
private:
	std::vector<ElementT> list;
public:
	/*Constructors*/
	RepositoryCars();
	RepositoryCars(const RepositoryCars& ot) :list{ ot.list } {};

	/*Add an element to the end of the list*/
	void push_back(const ElementT& el);

	/*Remove an specific element*/
	void erase(const ElementT& el);

	/*Update an element searched by id*/
	void update(const ElementT& el);

	/*Reads the data from a filename*/
	void read(std::string filename);

	/*Return the list*/
	std::vector<ElementT> getAll();

	/*Return the size of the list*/
	int size();
	/*Clears the repository*/
	void clear();


	/*Destructor*/
	~RepositoryCars();
};