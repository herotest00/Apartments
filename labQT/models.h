#pragma once
#include <QAbstractListModel>
#include <vector>
#include "service.h"

class ListModel: public QAbstractListModel
{
	std::vector<Apartment> elems;

public:

	ListModel(std::vector<Apartment> elems) :elems{ elems } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void loadData(std::vector<Apartment> elems);
};

