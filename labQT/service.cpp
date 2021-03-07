#include "service.h"
#include <string>
#include <random>
#include <Bits.h>
#include <numeric>
#include <iostream>

std::string ServiceException::getMessage() const
{
    return this->msg;
}


void UndoAdauga::doUndo()
{
    this->repoAparts.sterge(this->apart);
}

void UndoSterge::doUndo()
{
    this->repoAparts.adauga(this->apart);
}

void UndoModifica::doUndo()
{
    this->repoAparts.sterge(this->apart);
    this->repoAparts.adauga(this->apart);
}

void UndoCos::doUndo()
{
    this->repoList.sterge(this->apart);
}

int ServiceAparts::adauga(const int ID, const std::string name, const std::string type, const int surface)
{
    Apartment obj(ID, name, type, surface);
    this->validator.validare(obj);
    this->repoAparts.adauga(obj);
    this->undoActions.push_back(std::make_unique<UndoAdauga>(this->repoAparts, obj));
    return 0;
}

int ServiceAparts::modifica(const int ID, const std::string name, const std::string type, const int surface)
{
    Apartment obj(ID, name, type, surface);
    this->validator.validare(obj);
    const auto key = this->repoAparts.cautare(obj);
    if (key != INVALID_OBJ)
        this->undoActions.push_back(std::make_unique<UndoModifica>(this->repoAparts, this->repoAparts.getApart(key)));
    this->repoAparts.modifica(obj);
    return 0;
}

int ServiceAparts::sterge(const int ID)
{
    Apartment obj(ID);
    this->validator.validare(obj);
    const auto key = this->repoAparts.cautare(obj);
    if (key != INVALID_OBJ)
        this->undoActions.push_back(std::make_unique<UndoSterge>(this->repoAparts, this->repoAparts.getApart(key)));
    this->repoAparts.sterge(obj);
    return 0;
}

int ServiceAparts::cauta(const int ID)
{
    Apartment obj(ID);
    this->validator.validare(obj);
    const auto pos = this->repoAparts.cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    return 0;
}

std::vector<Apartment> ServiceAparts::getElems()
{
    return this->repoAparts.getElems();
}

std::vector<Apartment>* ServiceAparts::filtrare(bool(*filterFunction)(const Apartment&, void*), void* param)
{
    std::vector <Apartment>* filteredVector = new std::vector <Apartment>;
    std::vector <Apartment> Apartments = this->repoAparts.getElems();
    copy_if(Apartments.begin(), Apartments.end(), back_inserter(*filteredVector), [filterFunction, param](const Apartment& obj) {return filterFunction(obj, param); });
    return filteredVector;
}

std::vector<Apartment>* ServiceAparts::sortare(bool(*compareFunction)(const Apartment& obj1, const Apartment& obj2))
{
    std::vector <Apartment>* sortedVector = new std::vector <Apartment>;
    *sortedVector = this->repoAparts.getElems();
    std::sort(sortedVector->begin(), sortedVector->end(), compareFunction);
    return sortedVector;
}

int ServiceAparts::suma()
{
    std::vector <Apartment> vect = this->repoAparts.getElems();
    return std::accumulate(vect.begin(), vect.end(), 0, [](int sum, const Apartment& obj) {return obj.getSurface() + sum; });
}

std::string EntityCountDTO::getName() const
{
    return this->name;
}

std::string EntityCountDTO::getType() const
{
    return this->type;
}

int EntityCountDTO::getCount() const noexcept
{
    return this->count;
}

std::vector<EntityCountDTO>* ServiceAparts::getDTO()
{
    std::map <std::string, EntityCountDTO>dto;
    std::vector<Apartment> vect = this->repoAparts.getElems();
    for (const auto& obj : vect)
    {
        auto type = obj.getType();
        dto[type].count++;
        dto[type].type = type;
    }
    std::vector <EntityCountDTO>* v = new std::vector <EntityCountDTO>;
    for (const auto& obj : vect)
    {
        EntityCountDTO ecd;
        ecd.count = dto.at(obj.getType()).getCount();
        ecd.name = obj.getName();
        ecd.type = obj.getType();
        v->push_back(ecd);
    }
    return v;
}

void ServiceAparts::undo()
{
    if (this->undoActions.empty())
        throw ServiceException("Nu se poate face undo.\n");
    this->undoActions.back()->doUndo();
    this->undoActions.pop_back();
}


int ServiceList::adauga(const int ID)
{
    Apartment obj(ID);
    this->validator.validare(obj);
    const auto pos = this->repoAparts.cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    std::vector <Apartment> vect = this->repoAparts.getElems();
    auto it = find(vect.begin(), vect.end(), Apartment(pos));
    this->repoList.adauga(*it);
    this->undoActions.push_back(std::make_unique<UndoCos>(this->repoList, *it));
    return 0;
}

void ServiceList::sterge()
{
    while (this->repoList.getSize() > 0)
    {
        this->undoActions.clear();
        this->repoList.sterge(this->repoList.getElems().back());
    }
}

void ServiceList::genereaza(int count)
{
    if (count <= 0 || count > this->repoAparts.getSize())
        throw (RepoException("Nr. invalid.\n"));
    int rndNr = -1;
    std::vector<Apartment> aux = this->repoAparts.getElems();
    std::mt19937 mt{ std::random_device{}() };
    while (count > 0 && aux.size() > 0)
    {
        const std::uniform_int_distribution<> dist(0, aux.size() - 1);
        rndNr = dist(mt);
        if (this->repoList.cautare(aux.at(rndNr)) == INVALID_OBJ)
        {
            this->repoList.adauga(aux.at(rndNr));
            count--;
        }
        aux.erase(aux.begin() + rndNr);
    }
}

void ServiceList::Export(const std::string& filename)
{
    if (filename.find(".html") != filename.npos)
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "<!DOCTYPE html><html><head></head><body>";
        std::vector<Apartment> v = this->repoList.getElems();
        for (int i = 0; i < this->getSize(); i++)
            myfile << "<p><span style='font-weight: bold'>" << v.at(i).getID() << "</span>\t<span>" << v.at(i).getName() << "</span>\t<span>" << v.at(i).getType() << "</span>\t<span>" << v.at(i).getSurface() << "</span></p>";
        myfile << "</body></html>";
        myfile.close();
        return;
    }
    else if (filename.find(".csv") != filename.npos)
    {
        std::ofstream myfile;
        myfile.open(filename);
        std::vector<Apartment> v = this->repoList.getElems();
        for (int i = 0; i < this->getSize(); i++)
            myfile << v.at(i).getID() << ";" << v.at(i).getName() << ";" << v.at(i).getType() << ";" << v.at(i).getSurface() << "\n";
        myfile.close();
        return;
    }
}

int ServiceList::getSize() noexcept
{
    return this->repoList.getSize();
}

std::vector<Apartment> ServiceList::getElems()
{
    return this->repoList.getElems();
}

void ServiceList::undoCos()
{
    if (this->undoActions.empty())
        throw ServiceException("Nu se poate face undo.\n");
    this->undoActions.back()->doUndo();
    this->undoActions.pop_back();
}
