#include "MyListWidget.h"


MyListWidget::MyListWidget(MyListTableModel *tableModel, PictureDelegate *pictureDelegate, QWidget *parent)
	: tableModel(tableModel), pictureDelegate(pictureDelegate), QWidget(parent)
{
	ui.setupUi(this);

	this->ui.myListTableView->setModel(this->tableModel);
	this->setUpPictureTableView();
}

void MyListWidget::update()
{
	this->tableModel->updateModel();
}

void MyListWidget::setUpPictureTableView()
{
	//ui.myListTableView->setModel(this->tableModel);
	// set the custom delegate
	ui.myListTableView->setItemDelegate(this->pictureDelegate);

	//this->ui.myListTableView->setMaximumHeight(1000);
	// force the columns to resize, according to the size of their contents

	//this->ui.myListTableView->resizeColumnToContents(4);
	//this->ui.myListTableView->resizeRowsToContents();

	/*this->ui.myListTableView->resizeColumnsToContents();
	this->ui.myListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	this->ui.myListTableView->setVisible(true);*/

	//this->ui.myListTableView->resizeColumnsToContents();
	//this->ui.myListTableView->resizeRowsToContents();

	// hide the vertical header
	//this->ui.myListTableView->verticalHeader()->hide();
}

MyListWidget::~MyListWidget()
{
}
