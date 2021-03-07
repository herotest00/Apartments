#pragma once
#include "repo.h"
#include "validator.h"
#include <memory>

class ServiceException
{
private:
    std::string msg;

public:
    ServiceException(std::string msg) :msg{ msg } {};
    std::string getMessage() const;
};

/*clasa abstrasca*/
class ActiuneUndo
{
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};


class UndoAdauga :public ActiuneUndo
{
    Apartment apart;
    RepoAbstract& repoAparts;
public:
    UndoAdauga(RepoAbstract& repoAparts, const Apartment apart) :apart{ apart }, repoAparts{ repoAparts } {};
    void doUndo() override;
};


class UndoSterge :public ActiuneUndo
{
    Apartment apart;
    RepoAbstract& repoAparts;
public:
    UndoSterge(RepoAbstract& repoAparts, const Apartment apart) :apart{ apart }, repoAparts{ repoAparts } {};
    void doUndo() override;
};


class UndoModifica :public ActiuneUndo
{
    Apartment apart;
    RepoAbstract& repoAparts;
public:
    UndoModifica(RepoAbstract& repoAparts, const Apartment apart) :apart{ apart }, repoAparts{ repoAparts } {};
    void doUndo() override;
};


class UndoCos :public ActiuneUndo
{
    Apartment apart;
    RepoAbstract& repoList;
public:
    UndoCos(RepoAbstract& repoList, const Apartment apart) : apart{ apart }, repoList{ repoList } {};
    void doUndo() override;
};


class EntityCountDTO {
private:

    std::string name = "";
    std::string type = "";
    int count = 0;
    friend class ServiceAparts;

public:

    /*in: -
    getter pentru nume
    out: -*/
    std::string getName() const;

    /*in: -
    getter pentru tip
    out: -*/
    std::string getType() const;

    /*in: -
    getter pentru count
    out: -*/
    int getCount() const noexcept;

};


class ServiceAparts
{
private:

    RepoAbstract& repoAparts;
    Validator& validator;
    std::vector<std::unique_ptr<ActiuneUndo>> undoActions;

public:

    ServiceAparts(RepoAbstract& repoAparts, Validator& validator) noexcept : repoAparts{ repoAparts }, validator{ validator } {};

    /*in: ID, name, type, surface
    functie de adaugare in lista a unui obiect de tip Apartment
    out: 0 - daca s-a adaugat cu succes*/
    int adauga(const int ID, const std::string name, const std::string type, const int surface);

    /*in: ID - ID-ul elementului care va fi modificat
          name, type, surface - atribute noi
    functie de modificare a unui element
    out: 0 - daca s-a modificat cu succes*/
    int modifica(const int ID, const std::string name, const std::string type, const int surface);

    /*in: ID - ID-ul elementului care va fi sters
    functie de stergere a unui element
    out: 0 - daca s-a sters cu succes*/
    int sterge(const int ID);

    /*in: ID - ID-ul elementului care va fi cautat
    functie de cautare a unui element
    out: 0 - daca a fost gasit*/
    int cauta(const int ID);

    /*in: functie lambda de tip bool
          param - parametrul dupa care se face filtrarea
    functia filtreaza elementele dupa parametru
    out: un nou vector filtrat*/
    std::vector<Apartment>* filtrare(bool(*filterFunction)(const Apartment&, void*), void* param);

    /*in: functie lambda de tip bool
    functia sorteaza elementele
    out: un nou vector sortat*/
    std::vector<Apartment>* sortare(bool(*compareFunction)(const Apartment& obj1, const Apartment& obj2));

    /*in: -
    functie care creeaza un raport pe baza tipurilor
    out: vector cu raportul*/
    std::vector<EntityCountDTO>* getDTO();

    /*in: -
    functie de returnare a elementelor din lista
    out: vector cu elementele din lista*/
    std::vector<Apartment> getElems();

    /*in: -
    functie de undo
    out: -*/
    void undo();

    /*in: -
    functie de determinare a sumei
    out: suma suprafetei*/
    int suma();
};



class ServiceList
{
private:
    RepoAbstract& repoAparts;
    RepoAparts& repoList;
    Validator& validator;
    std::vector<std::unique_ptr<ActiuneUndo>>undoActions;

public:

    ServiceList(RepoAbstract& repoAparts, RepoAparts& repoList, Validator& validator) noexcept : repoAparts{ repoAparts }, repoList{ repoList }, validator{ validator } {};

    /*in: ID
    functie de adaugare in lista a unui obiect de tip Apartment
    out: 0 - daca s-a adaugat cu succes*/
    int adauga(const int ID);

    /*in: -
    functie de stergere a tuturor elementelor
    out: -*/
    void sterge();

    /*in: count
    functie de generare a unui nr de apartamente
    out: -*/
    void genereaza(const int count);

    /*in: filename
    functie */
    void Export(const std::string& filename);

    /*in: -
    functie de returnare a nr de elemente
    out: nr de elemente*/
    int getSize() noexcept;

    void undoCos();

    /*in: -
    functie de returnare a elementelor din lista
    out: vector cu elementele din lista*/
    std::vector<Apartment> getElems();
};
