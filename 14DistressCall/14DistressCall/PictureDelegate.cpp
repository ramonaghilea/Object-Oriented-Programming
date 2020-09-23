#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include <qcombobox.h>
#include "Evidence.h"

PictureDelegate::PictureDelegate(Repository* repository, QWidget* parent)
	: repository(repository), QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

	// show a picture only in the forth column, the other columns remain unchanged
	if (index.column() != 4)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}
	else
	{
		QString photo = QString::fromStdString(this->repository->getAllEvidenceFiles()[index.row()].getPhotograph());

		QPixmap pixMap(photo);
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() == 4)
	{
		return QSize(32, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);

	//auto hint = QStyledItemDelegate::sizeHint(option, index);

	//QFontMetrics fm(option.font);

	//std::unique_ptr<QWidget> editor(createEditor(nullptr, option, index));
	//auto comboBox = qobject_cast<QComboBox*>(editor.get());
	//if (comboBox != nullptr) {
	//	int width = 0;
	//	for (int ii = 0; ii < comboBox->count(); ++ii) {
	//		width = std::max(width, fm.width(comboBox->itemText(ii)) + 20);
	//	}
	//	hint.setWidth(std::max(hint.width(), width));
	//}

	//return hint;
}
