#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"

class MyListTableModel :
	public QAbstractTableModel
{
private:
	Repository* repository;

public:
	MyListTableModel(Repository* repository) : repository(repository) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	void updateModel();
};

