#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DistressCall.h"
#include "Service.h"
#include "MyListWidget.h"

class DistressCall : public QMainWindow
{
    Q_OBJECT

public:
	DistressCall(Service& service, MyListWidget* myListWidget, QWidget* parent = Q_NULLPTR);

private:
	Service& service;
	MyListWidget* myListWidget;
	Ui::DistressCallClass ui;

	void connectSignalsAndSlots();

	// mode A functionalities
	void populateList();
	//void connectSignalsAndSlots();
	int getSelectedIndex() const;

	void addEvidenceFile();
	void deleteEvidenceFile();
	void updateEvidenceFile();
	void addFileLocation();
	void addMyListLocation();

	// mode B functionalities

	//int getSelectedIndexMyList() const;

	void saveEvidenceFileMyList();
	void next();
	void populateFilteredList();
	void populateMyList();
	void myList();

	void myListTableView();

	void undo();
	void redo();
	void undoMyList();
	void redoMyList();

	void enableShortcut();
};
