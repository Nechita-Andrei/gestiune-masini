#include "RepoMasina.h"
#include <fstream>

RepositoryCars::RepositoryCars()
{
}

/*Add an element to the end of the list*/
void RepositoryCars::push_back(const ElementT& el) {
	for (const auto& x : list) {
		if (x.getID() == el.getID())
			throw Exception{ "The element already exists.\n" };
	}
	list.push_back(el);
}

/*Remove an specific element*/
void RepositoryCars::erase(const ElementT& el) {
	int i = 0;
	for (const auto& x : list) {
		if (x.getID() == el.getID()) {
			list.erase(list.begin() + i);
			return;
		}
		i++;
	}
	throw Exception{ "The element doesn't exists\n" };
}


/*Update an element searched by id*/
void RepositoryCars::update(const ElementT& el) {
	for (auto& x : list) {
		if (x.getID() == el.getID()) {
			x.setProducer(el.getProducer());
			x.setModel(el.getModel());
			x.setType(el.getType());
			return;
		}
	}
	throw Exception{ "The element doesn't exists\n" };
}

void RepositoryCars::read(std::string filename)
{
	clear();
	std::ifstream fin(filename);
	int id;
	std::string producer, model, type;
	while (fin >> id >> producer >> model >> type) {
		ElementT c{ id,producer,model,type };
		push_back(c);
	}
}

/*Return the list*/
std::vector<ElementT> RepositoryCars::getAll() {
	return list;
}

/*Return the size of the list*/
int RepositoryCars::size() {
	return list.size();
}

void RepositoryCars::clear()
{
	list.clear();
}

RepositoryCars::~RepositoryCars()
{
}
