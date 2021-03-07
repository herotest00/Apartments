#include "models.h"
#include <qdebug.h>

int ListModel::rowCount(const QModelIndex& parent) const
{
	return this->elems.size();
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		QString string;
		qDebug() << index.row();
		Apartment obj = elems.at(index.row());
		string += QString::number(obj.getID()) + " ";
		string += QString::fromStdString((obj.getName())) + " ";
		string += QString::fromStdString((obj.getType())) + " ";
		string += QString::number(obj.getSurface());
		return string;
	}
	if (index.row()%2==0 && role == Qt::BackgroundRole)
	return QVariant{};
}

void ListModel::loadData(std::vector<Apartment> elems)
{
	this->elems = elems;
	auto topLeft = createIndex(0, 0);
	auto bottomRight = createIndex(rowCount(), 0);
	emit dataChanged(topLeft, bottomRight);
}

