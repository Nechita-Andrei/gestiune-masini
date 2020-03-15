#pragma once
#include "ServiceMasina.h"
#include <QtWidgets/qapplication.h>
#include<QtWidgets/qmainwindow.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qmessagebox.h>
class GUI : public QWidget
{
private:


	ServiceCars s;
	QListWidget* list = new QListWidget;
	QPushButton* addBtn = new QPushButton{ "Add" };
	QPushButton* updateBtn = new QPushButton{ "Update" };
	QPushButton* deleteBtn = new QPushButton{ "Delete" };
	QPushButton* searchBtn = new QPushButton{ "Search" };
	QPushButton* sortByProducer = new QPushButton{ "SortByProducer" };
	QPushButton* sortByModel = new QPushButton{ "SortByModel" };
	QPushButton* sortByType = new QPushButton{ "SortByType" };


	QPushButton* filterByProducer = new QPushButton{ "FilterByProducer" };
	QPushButton* filterByType = new QPushButton{ "FilterByType" };
	QPushButton* filterByModel = new QPushButton{ "FilterByModel" };

	QPushButton* undoBtn = new QPushButton{ "Undo" };
	QPushButton* saveBtn = new QPushButton{ "Save" };
	QPushButton* loadBtn = new QPushButton{ "Load" };

	QLineEdit* textId = new QLineEdit;
	QLineEdit* textProducer = new QLineEdit;
	QLineEdit* textModel = new QLineEdit;
	QLineEdit* textType = new QLineEdit;


	void initComponents();
	void initSignalAndSlots();
	void initialState();

	void updateList(std::vector<Car> list);


	void addGUI();
	void updateGUI();
	void deleteGUI();
	void searchGUI();
	void sortNameGUI();
	void sortModelGUI();
	void sortTypeGUI();
	void filterProducerGUI();
	void filterModelGUI();
	void filterTypeGUI();

	void saveGUI();
	void loadGUI();
	void undoGUI();
public:
	GUI(ServiceCars& s) :s{ s } {
		setWindowIconText("Car App");
		initComponents();
		initSignalAndSlots();
		initialState();
	};
	~GUI();
};