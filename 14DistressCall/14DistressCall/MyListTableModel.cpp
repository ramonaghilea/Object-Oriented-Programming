#include "MyListTableModel.h"

int MyListTableModel::rowCount(const QModelIndex& parent) const
{
	//return this->repository->getNumberEvidenceFiles();
	int nr = this->repository->getNumberEvidenceFiles();
	return this->repository->getNumberEvidenceFiles();
}

int MyListTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant MyListTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	EvidenceFile currentEvidenceFile = this->repository->getAllEvidenceFiles()[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentEvidenceFile.getId());
		case 1:
			return QString::fromStdString(currentEvidenceFile.getMeasurement());
		case 2:
			return QString::fromStdString(std::to_string(currentEvidenceFile.getImageClarityLevel()));
		case 3:
			return QString::number(currentEvidenceFile.getQuantity());
		/*case 4:
			return QString::fromStdString(currentEvidenceFile.getPhotograph());*/
		default:
			break;
		}
	}
	return QVariant();
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Id");
			case 1:
				return QString("Measurement");
			case 2:
				return QString("ImageClarityLevel");
			case 3:
				return QString("Quantity");
			case 4:
				return QString("Photograph");
			default:
				break;
			}
		}
	}
	return QVariant();
}

void MyListTableModel::updateModel()
{
	this->beginResetModel();
	this->endResetModel();
}
