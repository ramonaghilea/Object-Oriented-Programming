#pragma once

#include <QWidget>
#include "ui_MyListWidget.h"
#include "MyListTableModel.h"
#include "Observer.h"
#include "PictureDelegate.h"

class MyListWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	MyListWidget(MyListTableModel* tableModel, PictureDelegate* pictureDelegate, QWidget *parent = Q_NULLPTR);
	void update() override;
	void setUpPictureTableView();
	~MyListWidget();

private:
	Ui::MyListWidget ui;
	MyListTableModel* tableModel;
	PictureDelegate* pictureDelegate;
};
