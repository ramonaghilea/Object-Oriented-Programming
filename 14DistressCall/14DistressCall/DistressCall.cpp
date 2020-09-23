#include "DistressCall.h"
#include <qmessagebox.h>
#include <qshortcut.h>

using namespace std;

DistressCall::DistressCall(Service& service, MyListWidget* myListWidget, QWidget *parent)
    : service(service), myListWidget(myListWidget), QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateList();
	this->populateMyList();
	this->connectSignalsAndSlots();
}

void DistressCall::populateList()
{
	this->ui.EvidenceFileWidget->clear();

	vector<EvidenceFile> allEvidenceFiles = this->service.getAllEvidenceFilesService();
	for (EvidenceFile& evidence : allEvidenceFiles)
		this->ui.EvidenceFileWidget->addItem(QString::fromStdString(evidence.EvidenceFileAsString()));
}

void DistressCall::connectSignalsAndSlots()
{
	QObject::connect(this->ui.EvidenceFileWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();

		if (selectedIndex < 0)
			return;

		EvidenceFile evidenceWithSelectedIndex = this->service.getAllEvidenceFilesService()[selectedIndex];
		this->ui.IdLineEdit->setText(QString::fromStdString(evidenceWithSelectedIndex.getId()));
		this->ui.MeasurementLineEdit->setText(QString::fromStdString(evidenceWithSelectedIndex.getMeasurement()));
		this->ui.ImageClarityLevelLineEdit->setText(QString::fromStdString(to_string(evidenceWithSelectedIndex.getImageClarityLevel())));
		this->ui.QuantityLineEdit->setText(QString::fromStdString(to_string(evidenceWithSelectedIndex.getQuantity())));
		this->ui.PhotographLineEdit->setText(QString::fromStdString(evidenceWithSelectedIndex.getPhotograph()));
		});

	QObject::connect(this->ui.AddButton, &QPushButton::clicked, this, &DistressCall::addEvidenceFile);
	QObject::connect(this->ui.DeleteButton, &QPushButton::clicked, this, &DistressCall::deleteEvidenceFile);
	QObject::connect(this->ui.UpdateButton, &QPushButton::clicked, this, &DistressCall::updateEvidenceFile);
	QObject::connect(this->ui.fileLocationButton, &QPushButton::clicked, this, &DistressCall::addFileLocation);
	QObject::connect(this->ui.myListLocationButton, &QPushButton::clicked, this, &DistressCall::addMyListLocation);

	QObject::connect(this->ui.SaveIdButton, &QPushButton::clicked, this, &DistressCall::saveEvidenceFileMyList);
	QObject::connect(this->ui.NextButton, &QPushButton::clicked, this, &DistressCall::next);
	QObject::connect(this->ui.FilteredListButton, &QPushButton::clicked, this, &DistressCall::populateFilteredList);
	QObject::connect(this->ui.MyListButton, &QPushButton::clicked, this, &DistressCall::myList);

	QObject::connect(this->ui.MyListTableButton, &QPushButton::clicked, this, &DistressCall::myListTableView);

	QObject::connect(this->ui.UndoButton, &QPushButton::clicked, this, &DistressCall::undo);
	QObject::connect(this->ui.RedoButton, &QPushButton::clicked, this, &DistressCall::redo);
	QObject::connect(this->ui.UndoMyListButton, &QPushButton::clicked, this, &DistressCall::undoMyList);
	QObject::connect(this->ui.RedoMyListButton, &QPushButton::clicked, this, &DistressCall::redoMyList);

	// create shortcut for undo
	QShortcut* shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	QObject::connect(shortcutUndo, &QShortcut::activated, this, &DistressCall::undo);

	// create shortcut for redo
	QShortcut* shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
	QObject::connect(shortcutRedo, &QShortcut::activated, this, &DistressCall::redo);

}

int DistressCall::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->ui.EvidenceFileWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) // if nothing is seleected
	{
		this->ui.IdLineEdit->clear();
		this->ui.MeasurementLineEdit->clear();
		this->ui.ImageClarityLevelLineEdit->clear();
		this->ui.QuantityLineEdit->clear();
		this->ui.PhotographLineEdit->clear();

		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();

	return selectedIndex;
}

void DistressCall::addEvidenceFile()
{
	string id = this->ui.IdLineEdit->text().toStdString();
	string measurement = this->ui.MeasurementLineEdit->text().toStdString();
	double imageClarityLevel = atof(this->ui.ImageClarityLevelLineEdit->text().toStdString().c_str());
	int quantity = atoi(this->ui.QuantityLineEdit->text().toStdString().c_str());
	string photograph = this->ui.PhotographLineEdit->text().toStdString();

	try
	{
		this->service.addEvidenceFileService(id, measurement, imageClarityLevel, quantity, photograph);
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}

	// update the gui
	this->populateList();

	int indexLastElement = this->service.getAllEvidenceFilesService().size() - 1;
	this->ui.EvidenceFileWidget->setCurrentRow(indexLastElement);
}

void DistressCall::deleteEvidenceFile()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No evidence file was selected");
		return;
	}

	EvidenceFile evidence = this->service.getAllEvidenceFilesService()[selectedIndex];
	this->service.deleteEvidenceFileService(evidence.getId());

	// update the gui
	this->populateList();
}

void DistressCall::updateEvidenceFile()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No evidence file was selected");
		return;
	}

	string id = this->ui.IdLineEdit->text().toStdString();
	string measurement = this->ui.MeasurementLineEdit->text().toStdString();
	double imageClarityLevel = atof(this->ui.ImageClarityLevelLineEdit->text().toStdString().c_str());
	int quantity = atoi(this->ui.QuantityLineEdit->text().toStdString().c_str());
	string photograph = this->ui.PhotographLineEdit->text().toStdString();

	this->service.updateEvidenceFileService(id, measurement, imageClarityLevel, quantity, photograph);

	// update the gui
	this->populateList();

	this->ui.EvidenceFileWidget->setCurrentRow(selectedIndex);
}

void DistressCall::addFileLocation()
{
	string filePath = this->ui.fileLocationLineEdit->text().toStdString();

	this->service.setDatabaseFilePath(filePath);

	// update the GUI list
	this->populateList();
}

void DistressCall::addMyListLocation()
{
	string filePath = this->ui.myListLocationLineEdit->text().toStdString();

	this->service.setMyListFilePath(filePath);
}

void DistressCall::saveEvidenceFileMyList()
{
	int index = this->service.getCurrentIndex();
	EvidenceFile evidence = this->service.getAllEvidenceFilesService()[index];
	try
	{
		this->service.saveEvidenceFileToMyListService(evidence.getId());
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}

	this->populateMyList();
}

void DistressCall::next()
{
	EvidenceFile currentEvidence = this->service.getNextEvidenceFileService();
	this->ui.currentEvidenceFileWidget->clear();
	this->ui.currentEvidenceFileWidget->addItem(QString::fromStdString(currentEvidence.EvidenceFileAsString()));
}

void DistressCall::populateFilteredList()
{
	this->ui.myListWidget->clear();

	std::string measurement = this->ui.MeasurementFilterLineEdit->text().toStdString();
	int minimumQuantity = atoi(this->ui.QuantityFilterLineEdit->text().toStdString().c_str());

	vector<EvidenceFile> filteredEvidenceFiles = this->service.getFilteredEvidenceFilesAfterMeasurementAndMinimumQuantityService(measurement, minimumQuantity);
	for (EvidenceFile& evidence : filteredEvidenceFiles)
		this->ui.myListWidget->addItem(QString::fromStdString(evidence.EvidenceFileAsString()));
}

void DistressCall::populateMyList()
{
	this->ui.myListWidget->clear();

	vector<EvidenceFile> filteredEvidenceFiles = this->service.getAllEvidenceFilesFromMyListService();
	for (EvidenceFile& evidence : filteredEvidenceFiles)
		this->ui.myListWidget->addItem(QString::fromStdString(evidence.EvidenceFileAsString()));
}

void DistressCall::myList()
{
	//std::string myListFilePath = this->service.getMyListFilePath();
	//std::string command = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" " + myListFilePath;

	//system(command.c_str());

	this->populateMyList();
	this->service.openExternalMyList();
}

void DistressCall::myListTableView()
{
	this->myListWidget->show();
}

void DistressCall::undo()
{
	try
	{
		this->service.undo();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
	this->populateList();
}

void DistressCall::redo()
{
	try
	{
		this->service.redo();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
	this->populateList();
}

void DistressCall::undoMyList()
{
	try
	{
		this->service.undoMyList();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
	this->populateMyList();
}

void DistressCall::redoMyList()
{
	try
	{
		this->service.redoMyList();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", exception.what());
		return;
	}
	this->populateMyList();
}

void DistressCall::enableShortcut()
{
}
