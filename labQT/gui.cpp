#include "GUI.h"
#include <random>

// GUI main
void mainGUI::initGUI()
{
    QHBoxLayout* mainLay = new QHBoxLayout;
    setLayout(mainLay);

    QVBoxLayout* lay1 = new QVBoxLayout;
    mainLay->addLayout(lay1);

    QFormLayout* elemsLay = new QFormLayout;
    elemsLay->addRow("ID", this->ID);
    elemsLay->addRow("Name", this->name);
    elemsLay->addRow("Type", this->type);
    elemsLay->addRow("Surface", this->surface);
    lay1->addLayout(elemsLay);

    QGridLayout* buttonsLay = new QGridLayout;
    buttonsLay->addWidget(this->addButton, 0, 0);
    buttonsLay->addWidget(this->delButton, 0, 1);
    buttonsLay->addWidget(this->modButton, 0, 2);
    buttonsLay->addWidget(this->FSButton, 1, 0);
    buttonsLay->addWidget(this->raportButton, 1, 1);
    buttonsLay->addWidget(this->sumaButton, 1, 2);
    buttonsLay->addWidget(this->undoButton, 2, 0);
    buttonsLay->addWidget(this->sortButtonLab, 2, 1);

    buttonsLay->addWidget(this->addListButton, 2, 2);
    buttonsLay->addWidget(this->delListButton, 3, 0);   
    buttonsLay->addWidget(this->generateListButton, 3, 1);
    buttonsLay->addWidget(this->exportListButton, 3, 2);
    buttonsLay->addWidget(this->undoListButton, 4, 0);
    buttonsLay->addWidget(this->exitButton, 4, 1);
    lay1->addLayout(buttonsLay);

    QHBoxLayout* cosbtnLay = new QHBoxLayout;
    cosbtnLay->addWidget(this->cosCRUDGUIButton);
    cosbtnLay->addWidget(this->cosReadOnlyGUIButton);

    QVBoxLayout* listbLay = new QVBoxLayout;
    listbLay->addWidget(this->list);
    listbLay->addLayout(cosbtnLay);
    mainLay->addLayout(listbLay);

    //LAB 11
    this->buttonsLab->setLayout(buttonsLabLayout);
    mainLay->addWidget(this->buttonsLab);
}

void mainGUI::initFiltrSort()
{
    QHBoxLayout* layout = new QHBoxLayout;
    this->FSWidget->setLayout(layout);

    QVBoxLayout* leftLayout = new QVBoxLayout;

    QFormLayout* textLayout = new QFormLayout;
    textLayout->addRow("Type", this->typeFS);
    textLayout->addRow("Surface", this->surfaceFS);

    QVBoxLayout* buttonFiltrLayout = new QVBoxLayout;
    buttonFiltrLayout->addWidget(this->filtrButton);

    QVBoxLayout* filtrLayout = new QVBoxLayout;
    filtrLayout->addLayout(textLayout);
    filtrLayout->addLayout(buttonFiltrLayout);

    QVBoxLayout* sortLayout = new QVBoxLayout;
    sortLayout->addWidget(nameBox);
    sortLayout->addWidget(typeBox);
    sortLayout->addWidget(surfaceBox);
    sortLayout->addWidget(sortButton);

    leftLayout->addLayout(filtrLayout);
    leftLayout->addLayout(sortLayout);
    layout->addLayout(leftLayout);
    layout->addWidget(this->listFS);
}

void mainGUI::loadData(std::vector<Apartment> elems, QListWidget* list)
{
    list->clear();
    QString string;
    for (const auto& obj : elems)
    {
        string += QString::number(obj.getID()) + " ";
        string += QString::fromStdString((obj.getName())) + " ";
        string += QString::fromStdString((obj.getType())) + " ";
        string += QString::number(obj.getSurface());
        list->addItem(string);
        string.clear();
    }
}

void mainGUI::addButtons(std::vector<Apartment> elems)
{
    if (this->buttonsLabLayout != NULL)
    {
        QLayoutItem* item;
        while ((item = this->buttonsLabLayout->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }
    for (const auto obj : elems)
    {
        QPushButton* button = new QPushButton(QString::fromStdString(obj.getName()));
        this->buttonsLabLayout->addWidget(button);
        QObject::connect(button, &QPushButton::clicked, [obj, this, button]()
            {
                this->serviceAparts.sterge(obj.getID());
                this->listModel->loadData(this->serviceAparts.getElems());
                //loadData(this->serviceAparts.getElems(), this->list);
                addButtons(this->serviceAparts.getElems());
            });
    }
}

void mainGUI::initConnect()
{
    QObject::connect(this->sortButtonLab, &QPushButton::clicked, [&]()
        {
            std::vector<Apartment>* elems = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getSurface() < obj2.getSurface(); });
            this->listModel->loadData(*elems);
            //loadData(*elems, this->list);
            addButtons(*elems);
            delete elems;
        });

    QObject::connect(this->addButton, &QPushButton::clicked, [&]()
        {
            try
            {
                auto ID = this->ID->text().toInt();
                auto name = this->name->text().toStdString();
                auto type = this->type->text().toStdString();
                auto surface = this->surface->text().toInt();
                serviceAparts.adauga(ID, name, type, surface);
                this->listModel->loadData(this->serviceAparts.getElems());
                //loadData(this->serviceAparts.getElems(), this->list);
                addButtons(this->serviceAparts.getElems());
            }
            catch (const RepoException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Adauga", message);
            }
            catch (const ValidException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Adauga", message);
            }
            catch (const ChaosException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Adauga", message);
            }
        });

    QObject::connect(this->delButton, &QPushButton::clicked, [&]()
        {
            try
            {
                auto ID = this->ID->text().toInt();
                serviceAparts.sterge(ID);
                this->listModel->loadData(this->serviceAparts.getElems());
                //loadData(this->serviceAparts.getElems(), this->list);
                addButtons(this->serviceAparts.getElems());
            }
            catch (const RepoException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Stergere", message);
            }
            catch (const ValidException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Stergere", message);
            }
            catch (const ChaosException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Stergere", message);
            }
        });

    QObject::connect(this->modButton, &QPushButton::clicked, [&]()
        {
            try
            {
                auto ID = this->ID->text().toInt();
                auto name = this->name->text().toStdString();
                auto type = this->type->text().toStdString();
                auto surface = this->surface->text().toInt();
                serviceAparts.modifica(ID, name, type, surface);
                this->listModel->loadData(this->serviceAparts.getElems());
                //loadData(this->serviceAparts.getElems(), this->list);
            }
            catch (const RepoException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Modifica", message);
            }
            catch (const ValidException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Modifica", message);
            }
            catch (const ChaosException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Modifica", message);
            }
        });

    QObject::connect(this->FSButton, &QPushButton::clicked, [&]()
        {
            this->FSWidget->show();
        });

    QObject::connect(this->filtrButton, &QPushButton::clicked, [&]()
        {
            this->listFS->clear();
            auto type = this->typeFS->text().toStdString();
            auto surface = this->surfaceFS->text().toInt();
            if (!type.empty() && surface == 0)
            {
                std::vector<Apartment>* elems = this->serviceAparts.filtrare([](const Apartment& obj, void* type) ->bool {return obj.getType() == *(std::string*)type; }, &type);
                loadData(*elems, this->listFS);
                delete elems;
            }
            else if (type.empty() && surface != 0)
            {
                std::vector<Apartment>* elems = this->serviceAparts.filtrare([](const Apartment& obj, void* surface) ->bool {return obj.getSurface() == *(int*)surface; }, &surface);
                loadData(*elems, this->listFS);
                delete elems;
            }
            else
                QMessageBox::information(nullptr, "Filtrare", "Filtrarea se face doar dupa tip sau suprafata!");
        });

    QObject::connect(this->sortButton, &QPushButton::clicked, [&]()
        {
            this->listFS->clear();
            if (this->surfaceBox->isChecked())
            {
                std::vector<Apartment>* elems = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getSurface() < obj2.getSurface(); });
                loadData(*elems, this->listFS);
                delete elems;
            }
            else if (this->typeBox->isChecked() && this->surfaceBox->isChecked())
            {
                std::vector<Apartment>* elems = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool { if (obj1.getType().compare(obj2.getType()) < 0) return true;  if (obj1.getSurface() < obj2.getSurface()) return true; return false; });
                loadData(*elems, this->listFS);
                delete elems;
            }
            else if (this->nameBox->isChecked())
            {
                std::vector<Apartment>* elems = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getName().compare(obj2.getName()) < 0; });
                loadData(*elems, this->listFS);
                delete elems;
            }
            else
                QMessageBox::information(nullptr, "Sortare", "Sortarea se face doar dupa nume, suprafata sau tip si suprafata!");
        });

    QObject::connect(this->undoButton, &QPushButton::clicked, [&]()
        {
            try
            {
                this->serviceAparts.undo();
                this->listModel->loadData(this->serviceAparts.getElems());
                //loadData(this->serviceAparts.getElems(), list);
            }
            catch (ServiceException & e)
            {
                QString string = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Undo", string);
            }
        });

    QObject::connect(this->raportButton, &QPushButton::clicked, [&]()
        {
            std::vector<EntityCountDTO>* vect = this->serviceAparts.getDTO();
            QString string;
            for (const auto& obj : *vect)
            {
                string = string + "Nume: " + QString::fromStdString(obj.getName()) + "---Tip: " + QString::fromStdString(obj.getType()) + "---Type Count: " + QString::number(obj.getCount()) + "\n";
            }
            QMessageBox::information(nullptr, "Raport", string);
        });

    QObject::connect(this->sumaButton, &QPushButton::clicked, [&]()
        {
            QString string = "Suma este ";
            string += QString::number(this->serviceAparts.suma());
            QMessageBox::information(nullptr, "Suma", string);
        });

    QObject::connect(this->cosCRUDGUIButton, &QPushButton::clicked, [&]()
        {
            CosCRUDGUI* gui = new CosCRUDGUI(*this);
            addObserver(gui);
            gui->show();
        });

    QObject::connect(this->cosReadOnlyGUIButton, &QPushButton::clicked, [&]()
        {
            CosReadOnlyGUI* gui = new CosReadOnlyGUI(*this);
            addObserver(gui);
            gui->show();
        });

    QObject::connect(this->exitButton, &QPushButton::clicked, []()
        {
            QApplication::quit();
        });


    QObject::connect(this->addListButton, &QPushButton::clicked, [&]()
        {
            try
            {
                this->serviceList.adauga(this->ID->text().toInt());
                this->notify();
            }
            catch (const RepoException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Adauga", message);
            }
            catch (const ValidException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Adauga", message);
            }
        });

    QObject::connect(this->delListButton, &QPushButton::clicked, [&]()
        {
            this->serviceList.sterge();
            this->notify();
        });

    QObject::connect(this->generateListButton, &QPushButton::clicked, [&]()
        {
            bool ok;
            int i = QInputDialog::getInt(this, "Genereaza", "Nr. elems: ", 0, 0, this->serviceAparts.getElems().size(), 1, &ok);
            if (ok)
            {
                this->serviceList.genereaza(i);
                this->notify();
            }
        });

    QObject::connect(this->exportListButton, &QPushButton::clicked, [&]()
        {
            auto filename = this->filenameCos->text().toStdString();
            this->serviceList.Export(filename);
        });

    QObject::connect(this->undoListButton, &QPushButton::clicked, [&]()
        {
            try
            {
                this->serviceList.undoCos();
                this->notify();
            }
            catch (const ServiceException & e)
            {
                auto message = QString::fromStdString(e.getMessage());
                QMessageBox::information(nullptr, "Undo", message);
            }
        });
}



// CosCRUDGUI

void CosCRUDGUI::update()
{
    this->list->clear();
    QString string;
    for (const auto& obj : this->main.serviceList.getElems())
    {
        string += QString::number(obj.getID()) + " ";
        string += QString::fromStdString((obj.getName())) + " ";
        string += QString::fromStdString((obj.getType())) + " ";
        string += QString::number(obj.getSurface());
        list->addItem(string);
        string.clear();
    }
}

void CosCRUDGUI::initGUI()
{
    QVBoxLayout* mainLay = new QVBoxLayout;
    this->setLayout(mainLay);

    mainLay->addWidget(this->list);

    QVBoxLayout* buttonsLay = new QVBoxLayout;
    buttonsLay->addWidget(this->delListButton);
    buttonsLay->addWidget(this->generateListButton);
    mainLay->addLayout(buttonsLay);
}

void CosCRUDGUI::initConnect()
{
    QObject::connect(this->delListButton, &QPushButton::clicked, [&]()
        {
            this->main.serviceList.sterge();
            this->main.notify();
        });

    QObject::connect(this->generateListButton, &QPushButton::clicked, [&]()
        {
            bool ok;
            int i = QInputDialog::getInt(this, "Genereaza", "Nr. elems: ", 0, 0, this->main.serviceAparts.getElems().size(), 1, &ok);
            if (ok)
            {
                this->main.serviceList.genereaza(i);
                this->main.notify();
            }
        });
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev)
{
    QPainter p{ this };
    for (const auto& obj : main.serviceList.getElems())
        p.drawEllipse(rand() % 400, rand() % 400, obj.getSurface(), obj.getID()*10);
}

void CosReadOnlyGUI::update()
{
    repaint();
}
