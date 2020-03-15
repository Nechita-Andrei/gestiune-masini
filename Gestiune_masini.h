#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gestiune_masini.h"

class Gestiune_masini : public QMainWindow
{
	Q_OBJECT

public:
	Gestiune_masini(QWidget *parent = Q_NULLPTR);

private:
	Ui::Gestiune_masiniClass ui;
};
