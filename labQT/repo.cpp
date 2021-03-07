#include "repo.h"
#include <iostream>
#include <exception>

RepoException::RepoException(const std::string msg) :msg{ msg } {}

std::string RepoException::getMessage() const
{
    return this->msg;
}


ChaosException::ChaosException(const std::string msg) : msg{ msg } {}

std::string ChaosException::getMessage() const
{
    return this->msg;
}


int RepoAparts::cautare(const Apartment& obj)
{
    auto it = this->Apartments.find(obj.getID());
    if (it != this->Apartments.end())
        return it->first;
    return INVALID_OBJ;
}

void RepoAparts::adauga(const Apartment& obj)
{
    if (cautare(obj) != INVALID_OBJ)
        throw (RepoException("ID deja existent.\n"));
    this->Apartments[obj.getID()] = obj;
}

void RepoAparts::modifica(const Apartment& obj)
{
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments[obj.getID()].setName(obj.getName());
    this->Apartments[obj.getID()].setType(obj.getType());
    this->Apartments[obj.getID()].setSurface(obj.getSurface());
}

void RepoAparts::sterge(const Apartment& obj)
{
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments.erase(obj.getID());
}

int RepoAparts::getSize() const noexcept
{
    return this->Apartments.size();
}

std::vector<Apartment> RepoAparts::getElems()
{
    std::vector<Apartment> aux;
    std::transform(this->Apartments.begin(), this->Apartments.end(), back_inserter(aux), [](std::pair<const int, Apartment>& per)->Apartment {return per.second; });
    return aux;
}

Apartment RepoAparts::getApart(int key)
{
    return this->Apartments[key];
}

//
int RepoFile::cautare(const Apartment& obj)
{
    auto it = this->Apartments.find(obj.getID());
    if (it != this->Apartments.end())
        return it->first;
    return INVALID_OBJ;
}

void RepoFile::adauga(const Apartment& obj)
{
    if (cautare(obj) != INVALID_OBJ)
        throw (RepoException("ID deja existent.\n"));
    this->Apartments[obj.getID()] = obj;
    writeToFile();
}

void RepoFile::modifica(const Apartment& obj)
{
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments[obj.getID()].setName(obj.getName());
    this->Apartments[obj.getID()].setType(obj.getType());
    this->Apartments[obj.getID()].setSurface(obj.getSurface());
    writeToFile();
}

void RepoFile::sterge(const Apartment& obj)
{
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments.erase(obj.getID());
    writeToFile();
}

int RepoFile::getSize() const noexcept
{
    return this->Apartments.size();
}

std::vector<Apartment> RepoFile::getElems()
{
    std::vector<Apartment> aux;
    std::transform(this->Apartments.begin(), this->Apartments.end(), back_inserter(aux), [](std::pair<const int, Apartment>& per)->Apartment {return per.second; });
    return aux;
}

Apartment RepoFile::getApart(int key)
{
    return this->Apartments[key];
}

void RepoFile::loadFromFile()
{
    std::ifstream fin(this->filename);
    if (!fin.is_open())
        throw RepoException("Fisierul nu s-a putut deschide.\n");
    int ID = 0, surface = 0;
    std::string name, type;
    while (!fin.eof())
    {
        fin >> ID >> name >> type >> surface;
        if (fin.eof())
            break;
        Apartment obj{ ID, name, type, surface };
        this->Apartments[obj.getID()] = obj;
    }
    fin.close();
}

void RepoFile::writeToFile()
{
    std::ofstream fout(this->filename);
    /*if (!fout.is_open())
        throw RepoException("Fisierul nu s-a putut deschide.\n");*/
    for (auto& obj : getElems())
        fout << obj.getID() << std::endl << obj.getName() << std::endl << obj.getType() << std::endl << obj.getSurface() << std::endl;
    fout.close();
}

//
void RepoLab::adauga(const Apartment& obj)
{
    const auto r = ((double)rand() / (RAND_MAX));
    if (r < this->prob)
        throw ChaosException("Fail!\n");
    if (cautare(obj) != INVALID_OBJ)
        throw (RepoException("ID deja existent.\n"));
    this->Apartments[obj.getID()] = obj;
}

void RepoLab::modifica(const Apartment& obj)
{
    const auto r = ((double)rand() / (RAND_MAX));
    if (r < this->prob)
        throw ChaosException("Fail!\n");
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments[obj.getID()].setName(obj.getName());
    this->Apartments[obj.getID()].setType(obj.getType());
    this->Apartments[obj.getID()].setSurface(obj.getSurface());
}

void RepoLab::sterge(const Apartment& obj)
{
    const auto r = ((double)rand() / (RAND_MAX));
    if (r < this->prob)
        throw ChaosException("Fail!\n");
    const auto pos = cautare(obj);
    if (pos == INVALID_OBJ)
        throw (RepoException("ID inexistent.\n"));
    this->Apartments.erase(obj.getID());
}

int RepoLab::cautare(const Apartment& obj)
{
    const auto r = ((double)rand() / (RAND_MAX));
    if (r < this->prob)
        throw ChaosException("Fail!\n");
    auto it = this->Apartments.find(obj.getID());
    if (it != this->Apartments.end())
        return it->first;
    return INVALID_OBJ;
}

int RepoLab::getSize() const noexcept
{
    return this->Apartments.size();
}

std::vector<Apartment> RepoLab::getElems()
{
    std::vector<Apartment> aux;
    std::transform(this->Apartments.begin(), this->Apartments.end(), back_inserter(aux), [](std::pair<const int, Apartment>& per)->Apartment {return per.second; });
    return aux;
}

Apartment RepoLab::getApart(int key)
{
    return this->Apartments[key];
}
//
