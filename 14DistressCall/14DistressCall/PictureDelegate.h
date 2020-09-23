#pragma once
#include <QStyledItemDelegate>
#include "Repository.h"

class PictureDelegate : public QStyledItemDelegate
{
private:
	Repository* repository;
public:
	PictureDelegate(Repository* repository, QWidget* parent = 0);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

