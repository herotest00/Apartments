#pragma once

#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QObject>
#include <qdebug.h>
#include <QMessageBox>
#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QInputDialog>
#include "observer.h"
#include <qlistview.h>
#include <qpainter.h>
#include <qlistview.h>
#include "models.h"

class mainGUI : public QWidget, public Observable
{
    friend class CosCRUDGUI;
    friend class CosReadOnlyGUI;

private:
    ServiceList& serviceList;
    ServiceAparts& serviceAparts;

    // MAIN
    QWidget* FSWidget = new QWidget;
    QWidget* buttonsLab = new QWidget;
    QVBoxLayout* buttonsLabLayout = new QVBoxLayout;
    QListView* list = new QListView;
    ListModel* listModel = new ListModel(this->serviceAparts.getElems());
    //QListWidget* list = new QListWidget;
    QListWidget* listFS = new QListWidget;

    QPushButton* addButton = new QPushButton("&Adauga");
    QPushButton* delButton = new QPushButton("&Sterge");
    QPushButton* modButton = new QPushButton("&Modifica");
    QPushButton* FSButton = new QPushButton("&Filtrare/Sortare");
    //LAB11
    QPushButton* sortButtonLab = new QPushButton("SortareLab");
    //LAB11
    QPushButton* raportButton = new QPushButton("&Raport");
    QPushButton* sumaButton = new QPushButton("&Suma");
    QPushButton* undoButton = new QPushButton("&Undo");
    QPushButton* exitButton = new QPushButton("&Exit");

    // FILTRARE/SORTARE
    QLineEdit* ID = new QLineEdit;
    QLineEdit* name = new QLineEdit;
    QLineEdit* type = new QLineEdit;
    QLineEdit* surface = new QLineEdit;
    QLineEdit* typeFS = new QLineEdit;
    QLineEdit* surfaceFS = new QLineEdit;

    QCheckBox* typeBox = new QCheckBox("Type");
    QCheckBox* surfaceBox = new QCheckBox("Surface");
    QCheckBox* nameBox = new QCheckBox("Name");

    QPushButton* filtrButton = new QPushButton("&Filtrare");
    QPushButton* sortButton = new QPushButton("Sortare");


    // COS
    QLineEdit* IDCos = new QLineEdit;
    QLineEdit* filenameCos = new QLineEdit;

    QPushButton* addListButton = new QPushButton("&Adauga cos");
    QPushButton* delListButton = new QPushButton("&Golire cos");
    QPushButton* generateListButton = new QPushButton("&Genereaza cos");
    QPushButton* exportListButton = new QPushButton("&Export cos");
    QPushButton* undoListButton = new QPushButton("&Undo cos");
    
    QPushButton* cosCRUDGUIButton = new QPushButton("&CosCRUDGUI");
    QPushButton* cosReadOnlyGUIButton = new QPushButton("&CosReadOnlyGUI");
    

    void initGUI();

    void initFiltrSort();

    void loadData(std::vector<Apartment> elems, QListWidget* list);

    void addButtons(std::vector<Apartment> elems);

    void initConnect();

public:

    mainGUI() = default;

    mainGUI(ServiceAparts& serviceAparts, ServiceList& serviceList) : serviceAparts{ serviceAparts }, serviceList{ serviceList }
    {
        initGUI();
        initFiltrSort();
        this->list->setUniformItemSizes(true);
        this->list->setModel(this->listModel);
        addButtons(this->serviceAparts.getElems());
        initConnect();
    }
};



class CosCRUDGUI : public QWidget, public Observer
{
private:

    mainGUI& main;

    QPushButton* delListButton = new QPushButton("&Sterge");
    QPushButton* generateListButton = new QPushButton("&Genereaza");

    QListWidget* list = new QListWidget;

    void initGUI();

    void initConnect();

    void update() override;

public:

    CosCRUDGUI(mainGUI& mainGUI) : main{ mainGUI }
    {
        initGUI();
        update();
        initConnect();
    }

    ~CosCRUDGUI()
    {
        this->main.delObserver(this);
    }
};


class CosReadOnlyGUI : public QWidget, public Observer
{
    mainGUI& main;

    void update() override;

public:

    CosReadOnlyGUI(mainGUI& mainGUI) :main{ mainGUI }
    {
        update();
    }

    void paintEvent(QPaintEvent* ev) override;

    ~CosReadOnlyGUI()
    { 
        this->main.delObserver(this);
    }
};