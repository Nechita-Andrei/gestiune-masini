#include "GUI.h"
void GUI::initComponents()
{
	QHBoxLayout* mainL = new QHBoxLayout;
	setLayout(mainL);

	QVBoxLayout* rightL = new QVBoxLayout;
	rightL->addWidget(list);

	QHBoxLayout* btn1L = new QHBoxLayout;
	btn1L->addWidget(deleteBtn);
	btn1L->addWidget(sortByProducer);
	btn1L->addWidget(sortByModel);
	btn1L->addWidget(sortByType);
	rightL->addLayout(btn1L);
	rightL->addStretch();
	mainL->addLayout(rightL);

	QVBoxLayout* leftL = new QVBoxLayout;

	QFormLayout* dataL = new QFormLayout;
	dataL->addRow("ID", textId);
	dataL->addRow("Producer", textProducer);
	dataL->addRow("Model", textModel);
	dataL->addRow("Type", textType);

	QHBoxLayout* btnL2 = new QHBoxLayout;
	btnL2->addWidget(addBtn);
	btnL2->addWidget(updateBtn);
	btnL2->addWidget(searchBtn);
	QHBoxLayout* btnL3 = new QHBoxLayout;
	btnL3->addWidget(filterByProducer);
	btnL3->addWidget(filterByModel);
	btnL3->addWidget(filterByType);
	QHBoxLayout* btnL4 = new QHBoxLayout;
	btnL4->addWidget(saveBtn);
	btnL4->addWidget(loadBtn);
	btnL4->addWidget(undoBtn);


	leftL->addLayout(dataL);
	leftL->addLayout(btnL2);
	leftL->addLayout(btnL3);
	leftL->addStretch();
	leftL->addLayout(btnL4);
	mainL->addLayout(leftL);
}

void GUI::initSignalAndSlots()
{
	QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
		if (list->selectedItems().isEmpty()) {
			textId->setText("");
			textProducer->setText("");
			textModel->setText("");
			textType->setText("");
			deleteBtn->setEnabled(false);

			return;
		}
		auto item = list->selectedItems().at(0);
		int i = item->data(Qt::UserRole).toInt();
		Car c = s.searchCar(i);
		textId->setText(QString::number(c.getID()));
		textProducer->setText(QString::fromStdString(c.getProducer()));
		textModel->setText(QString::fromStdString(c.getModel()));
		textType->setText(QString::fromStdString(c.getType()));
		deleteBtn->setEnabled(true);
		sortByProducer->setEnabled(true);
		sortByModel->setEnabled(true);
		sortByType->setEnabled(true);

		});

	QObject::connect(addBtn, &QPushButton::clicked, this, &GUI::addGUI); // add button;
	QObject::connect(updateBtn, &QPushButton::clicked, this, &GUI::updateGUI); // update button;
	QObject::connect(deleteBtn, &QPushButton::clicked, this, &GUI::deleteGUI); // delete button;
	QObject::connect(searchBtn, &QPushButton::clicked, this, &GUI::searchGUI); // search button;
	QObject::connect(sortByProducer, &QPushButton::clicked, this, &GUI::sortNameGUI); // sortbyname button;
	QObject::connect(sortByModel, &QPushButton::clicked, this, &GUI::sortModelGUI); // sortbymodel button;
	QObject::connect(sortByType, &QPushButton::clicked, this, &GUI::sortTypeGUI); // sortbytype button;
	QObject::connect(filterByProducer, &QPushButton::clicked, this, &GUI::filterProducerGUI); // filterbytype button;
	QObject::connect(filterByModel, &QPushButton::clicked, this, &GUI::filterModelGUI); // filterbytype button;
	QObject::connect(filterByType, &QPushButton::clicked, this, &GUI::filterTypeGUI); // filterbytype button;
	QObject::connect(saveBtn, &QPushButton::clicked, this, &GUI::saveGUI); // save button
	QObject::connect(loadBtn, &QPushButton::clicked, this, &GUI::loadGUI); // load button
	QObject::connect(undoBtn, &QPushButton::clicked, this, &GUI::undoGUI); // undo button

}

void GUI::initialState()
{
	updateList(s.getAll());
	deleteBtn->setEnabled(false);
	undoBtn->setEnabled(false);


	if (s.size() == 0) {
		updateBtn->setEnabled(false);
		sortByModel->setEnabled(false);
		sortByProducer->setEnabled(false);
		sortByType->setEnabled(false);
		filterByType->setEnabled(false);
		filterByProducer->setEnabled(false);
		filterByModel->setEnabled(false);
		searchBtn->setEnabled(false);
		saveBtn->setEnabled(false);
	}
}

void GUI::updateList(std::vector<Car> new_list)
{
	list->clear();
	int i = 0;
	for (const auto c : new_list) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c.toString2()));
		if (i % 2)
			item->setData(Qt::BackgroundRole, QColor(0, 0, 15, 20));
		item->setData(Qt::UserRole, c.getID());
		list->addItem(item);
		i++;
	}
}

void GUI::addGUI()
{

	int id = textId->text().toInt();
	string producer = textProducer->text().toStdString();
	string model = textModel->text().toStdString();
	string type = textType->text().toStdString();
	try {
		s.storeCar(id, producer, model, type);
		updateList(s.getAll());
		saveBtn->setEnabled(true);
		undoBtn->setEnabled(s.canUndo());
	}
	catch (Exception & e) {
		QMessageBox::warning(nullptr, "Error", QString::fromStdString(e.getMessage()));
	}



}

void GUI::updateGUI()
{
	int id = textId->text().toInt();
	string producer = textProducer->text().toStdString();
	string model = textModel->text().toStdString();
	string type = textType->text().toStdString();
	try {
		s.updateCar(id, producer, model, type);
		updateList(s.getAll());
		saveBtn->setEnabled(true);
		undoBtn->setEnabled(s.canUndo());
	}
	catch (Exception & e) {
		QMessageBox::warning(nullptr, "Error", QString::fromStdString(e.getMessage()));
	}

	updateList(s.getAll());

}

void GUI::deleteGUI()
{
	int id = textId->text().toInt();
	try {
		s.deleteCar(id);
		updateList(s.getAll());
		saveBtn->setEnabled(true);
		undoBtn->setEnabled(s.canUndo());
	}
	catch (Exception & e) {
		QMessageBox::warning(nullptr, "Error", QString::fromStdString(e.getMessage()));
	}

	updateList(s.getAll());
}

void GUI::searchGUI()
{
	int id = textId->text().toInt();
	Car c;
	try {
		c = s.searchCar(id);
		std::vector<Car> new_list;
		new_list.push_back(c);

		updateList(new_list);
		//updateList(s.getAll());
		//saveBtn->setEnabled(true);
		undoBtn->setEnabled(s.canUndo());
	}
	catch (Exception & e) {
		updateList(s.getAll());
		QMessageBox::warning(nullptr, "Error", QString::fromStdString(e.getMessage()));

	}


}

void GUI::sortNameGUI()
{
	updateList(s.sortCars(1, 0));
}

void GUI::sortModelGUI()
{
	updateList(s.sortCars(2, 0));
}

void GUI::sortTypeGUI()
{
	updateList(s.sortCars(3, 0));
}

void GUI::filterProducerGUI()
{
	string str = textProducer->text().toStdString();
	updateList(s.filterCar(0, str));

}

void GUI::filterModelGUI()
{
	string str = textModel->text().toStdString();
	updateList(s.filterCar(1, str));
}

void GUI::filterTypeGUI()
{
	string str = textType->text().toStdString();
	updateList(s.filterCar(2, str));
}

void GUI::saveGUI()
{
	s.saveCars();
	saveBtn->setEnabled(false);
}

void GUI::loadGUI()
{
	s.loadCars();
	if (s.size() != 0) {
		saveBtn->setEnabled(true);
		sortByProducer->setEnabled(true);
		sortByModel->setEnabled(true);
		sortByType->setEnabled(true);
		filterByType->setEnabled(true);
		filterByProducer->setEnabled(true);
		filterByModel->setEnabled(true);
		updateBtn->setEnabled(true);
		searchBtn->setEnabled(true);
	}
	updateList(s.getAll());
}

void GUI::undoGUI()
{

	s.doUndo();
	updateList(s.getAll());
	undoBtn->setEnabled(s.canUndo());
	saveBtn->setEnabled(true);

}

GUI::~GUI()
{
}
