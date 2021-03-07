#include <iostream>
#include "ui.h"


void UI::afisare(const std::vector<Apartment> vector) const
{
    for (const auto& obj : vector)
        std::cout << "ID: " << obj.getID() << "  Nume: " << obj.getName() << "  Tip: " << obj.getType() << "  Suprafata: " << obj.getSurface() << "\n";
}

void UI::afisareCount() const
{
    std::cout << "Nr. apartamente in lista: " << this->serviceList.getSize() << "\n\n";
}

std::string UI::readString(const std::string message) const
{
    std::string string;
    std::cout << message;
    std::cin >> string;
    return string;
}

int UI::readInt(const std::string message) const
{
    int ID;
    std::cout << message;
    std::cin >> ID;
    return ID;
}

void UI::adaugaAparts()
{
    const int ID = readInt("ID: ");
    std::string name = readString("Nume: ");
    std::string type = readString("Type: ");
    const int surface = readInt("Suprafata: ");
    this->serviceAparts.adauga(ID, name, type, surface);
}

void UI::modificaAparts()
{
    int const ID = readInt("ID: ");
    std::string name = readString("Nume: ");
    std::string type = readString("Type: ");
    const int surface = readInt("Suprafata: ");
    this->serviceAparts.modifica(ID, name, type, surface);
}

void UI::stergeAparts()
{
    const int ID = readInt("ID: ");
    this->serviceAparts.sterge(ID);
}

void UI::cautaAparts()
{
    const int ID = readInt("ID: ");
    this->serviceAparts.cauta(ID);
}

void UI::filtrareAparts()
{
    std::map<std::string, int> map{ {"tip", 1}, {"suprafata", 2} };
    std::string cmd = readString("1. tip\n2. suprafata\n");
    std::string type{ " " };
    std::vector<Apartment>* vector;
    int surface{ 0 };
    switch (map[cmd])
    {
    case 1:
        type = readString("Tip: ");
        vector = this->serviceAparts.filtrare([](const Apartment& obj, void* type) ->bool {return obj.getType() == *(std::string*)type; }, &type);
        afisare(*vector);
        delete vector;
        break;
    case 2:
        surface = readInt("Suprafata: ");
        vector = this->serviceAparts.filtrare([](const Apartment& obj, void* surface) ->bool {return obj.getSurface() == *(int*)surface; }, &surface);
        afisare(*vector);
        delete vector;
        break;
    default:
        std::cout << "Filtrare invalida.\n";
    }
}

void UI::sortareAparts()
{
    std::map<std::string, int> map{ {"nume", 1}, {"suprafata", 2}, {"tip+suprafata", 3} };
    std::string cmd = readString("1. nume\n2. suprafata\n3. tip+suprafat\n");
    std::vector<Apartment>* vector;
    switch (map[cmd])
    {
    case 1:
        vector = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getName().compare(obj2.getName()) < 0; });
        afisare(*vector);
        delete vector;
        break;
    case 2:
        vector = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getSurface() < obj2.getSurface(); });
        afisare(*vector);
        delete vector;
        break;
    case 3:
        vector = this->serviceAparts.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool { if (obj1.getType().compare(obj2.getType()) < 0) return true;  if (obj1.getSurface() < obj2.getSurface()) return true; return false; });
        afisare(*vector);
        delete vector;
        break;
    default:
        std::cout << "Sortare invalida.\n";
    }
}

void UI::adaugaList()
{
    const int ID = readInt("ID: ");
    this->serviceList.adauga(ID);
}

void UI::stergeList()
{
    this->serviceList.sterge();
}

void UI::genereazaList()
{
    const int count = readInt("Nr. de elemente: ");
    this->serviceList.genereaza(count);
}

void UI::Export()
{
    const std::string filename = readString("Nume fisier: ");
    this->serviceList.Export(filename);
}

void UI::undo()
{
    this->serviceAparts.undo();
}

void UI::undoCos()
{
    this->serviceList.undoCos();
}

void UI::menu0()
{
    std::cout << "1. apartament\n2. lista\n";
}

void UI::menu1()
{
    std::cout << "1. adauga\n2. modifica\n3. sterge\n4. cauta\n5. filtrare\n6. sortare\n7. afisare\n8. undo\n";
}

void UI::menu2()
{
    std::cout << "1. adauga\n2. sterge\n3. genereaza\n4. afisare\n5. export\n6. undo\n";
}

void UI::run()
{
    std::map <std::string, int> map1{ {"adauga", 1}, {"modifica", 2}, {"sterge", 3}, {"cauta", 4}, {"filtrare", 5}, {"sortare", 6} , {"afisare", 7}, {"suma", 8}, {"undo", 9} };
    std::map <std::string, int> map2{ {"adauga", 1}, {"sterge", 2}, {"genereaza", 3} ,{"afisare", 4}, {"export", 5}, {"undo", 6} };
    while (true)
    {
        menu0();
        std::string cmd = readString("Optiune: ");
        if (cmd.compare("apartament") == 0)
        {
            menu1();
            cmd = readString("Optiune: ");
            switch (map1[cmd])
            {
            case 1:
                try
                {
                    adaugaAparts();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ValidException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ChaosException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 2:
                try
                {
                    modificaAparts();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ValidException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ChaosException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 3:
                try
                {
                    stergeAparts();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ValidException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ChaosException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 4:
                try
                {
                    cautaAparts();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ValidException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ChaosException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 5:
                filtrareAparts();
                afisareCount();
                break;
            case 6:
                sortareAparts();
                afisareCount();
                break;
            case 7:
                afisare(this->serviceAparts.getElems());
                afisareCount();
                break;
            case 8:
                std::cout << this->serviceAparts.suma();
                break;
            case 9:
                try
                {
                    undo();
                }
                catch (const ServiceException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 0:
                break;
            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
        else if (cmd.compare("lista") == 0)
        {
            menu2();
            cmd = readString("Optiune: ");
            switch (map2[cmd])
            {
            case 1:
                try
                {
                    adaugaList();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                catch (const ValidException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 2:
                stergeList();
                afisareCount();
                break;
            case 3:
                try
                {
                    genereazaList();
                }
                catch (const RepoException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 4:
                afisare(this->serviceList.getElems());
                std::cout << "\n";
                break;
            case 5:
                Export();
                break;
            case 6:
                try
                {
                    undoCos();
                }
                catch (const ServiceException & e)
                {
                    std::cout << e.getMessage();
                }
                afisareCount();
                break;
            case 0:
                break;
            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
        else if (cmd.compare("0") == 0)
            return;
        else
            std::cout << "Optiune invalida.\n";
    }

}
