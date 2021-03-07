#pragma once
#include <vector>
#include "domain.h"
#include <algorithm>
#include <map>
#include <fstream>

#define INVALID_OBJ -1

class RepoException
{
private:
    std::string msg;

public:

    RepoException(const std::string msg);

    std::string getMessage() const;
};


class ChaosException
{
private:
    std::string msg;

public:

    ChaosException(const std::string msg);

    std::string getMessage() const;
};


class RepoAbstract
{
protected:
    std::map<int, Apartment> Apartments;

public:
    /*in: obj
    functie de cautare a unui obiect
    out: pozitia din lista daca exista
         -1 daca nu exista elementul*/
    virtual int cautare(const Apartment& obj) = 0;

    /*in: obj - obiect de tip apartament
    functie de adaugare in lista
    out: -*/
    virtual void adauga(const Apartment& obj) = 0;

    /*in: obj - obiect de tip apartament
    functie de modificare a unui element din lista
    out: -*/
    virtual void modifica(const Apartment& obj) = 0;

    /*in: obj - obiect de tip apartament
    functie de stergere a unui element din lista
    out: -*/
    virtual void sterge(const Apartment& obj) = 0;

    /*in: -
    functie de returnare a numarului de elemente din lista
    out: nr de elemente*/
    virtual int getSize() const noexcept = 0;

    /*in: -
    functie de returnare a listei
    out: lista*/
    virtual std::vector<Apartment> getElems() = 0;

    /*in: key - ID
    functie de returnare a unui obiect
    out: apartament*/
    virtual Apartment getApart(int key) = 0;

    virtual ~RepoAbstract() = default;
};


class RepoAparts : public RepoAbstract
{
public:

    /*functie suprascrisa de cautare*/
    int cautare(const Apartment& obj) override;

    /*functie suprascrisa de adaugare*/
    void adauga(const Apartment& obj) override;

    /*functie suprascrisa de modificare*/
    void modifica(const Apartment& obj) override;

    /*functie suprascrisa de stergere*/
    void sterge(const Apartment& obj) override;

    /*in: -
    functie de returnare a numarului de elemente din lista
    out: nr de elemente*/
    int getSize() const noexcept override;

    /*in: -
    functie de returnare a listei
    out: lista*/
    std::vector<Apartment> getElems() override;

    /*in: key - ID
    functie de returnare a unui obiect
    out: apartament*/
    Apartment getApart(int key) override;

    /*destructor default pentru mostenire*/
    ~RepoAparts() = default;
};


class RepoFile :public RepoAbstract
{
private:
    std::string filename;

public:
    RepoFile(std::string filename) :filename{ filename }, RepoAbstract()
    {
        loadFromFile();
    }

    /*functie de citire din fisier*/
    void loadFromFile();

    /*functie de scriere in fisier*/
    void writeToFile();

    /*functie suprascrisa de cautare*/
    int cautare(const Apartment& obj) override;

    /*functie suprascrisa de adaugare*/
    void adauga(const Apartment& obj) override;

    /*functie suprascrisa de modificare*/
    void modifica(const Apartment& obj) override;

    /*functie suprascrisa de stergere*/
    void sterge(const Apartment& obj) override;

    /*in: -
    functie de returnare a numarului de elemente din lista
    out: nr de elemente*/
    int getSize() const noexcept override;

    /*in: -
    functie de returnare a listei
    out: lista*/
    std::vector<Apartment> getElems() override;

    /*in: key - ID
    functie de returnare a unui obiect
    out: apartament*/
    Apartment getApart(int key) override;
};

class RepoLab :public RepoAbstract
{
private:
    double prob = 0;

public:
    RepoLab(double prob) :prob{ prob }, RepoAbstract() {};

    /*functie suprascrisa de cautare*/
    int cautare(const Apartment& obj) override;

    /*functie suprascrisa de adaugare*/
    void adauga(const Apartment& obj) override;

    /*functie suprascrisa de modificare*/
    void modifica(const Apartment& obj) override;

    /*functie suprascrisa de stergere*/
    void sterge(const Apartment& obj) override;

    /*in: -
    functie de returnare a numarului de elemente din lista
    out: nr de elemente*/
    int getSize() const noexcept override;

    /*in: -
    functie de returnare a listei
    out: lista*/
    std::vector<Apartment> getElems() override;

    /*in: key - ID
    functie de returnare a unui obiect
    out: apartament*/
    Apartment getApart(int key) override;
};
