#pragma once

#include <assert.h>
#include "ui.h"
#include <iostream>
#include <memory>

void runDomain()
{
    Apartment obj{ 5, "Marcel", "Garsoniera", 50 };
    assert(obj.getID() == 5);
    assert(obj.getName() == "Marcel");
    assert(obj.getType() == "Garsoniera");
    assert(obj.getSurface() == 50);

    obj.setID(6);
    obj.setName("Ghita");
    obj.setType("EASD");
    obj.setSurface(80);
    assert(obj.getID() == 6);
    assert(obj.getName() == "Ghita");
    assert(obj.getType() == "EASD");
    assert(obj.getSurface() == 80);

    Apartment obj1{ 1 };
    assert(obj1.getID() == 1);
    assert(obj1.getName() == " ");
    assert(obj1.getType() == " ");
    assert(obj1.getSurface() == 1);

    obj1.setID(6);
    assert(obj == obj1);
}

void runValidator()
{
    Validator validator;
    Apartment obj{ -1, "", "", -1 };

    try
    {
        validator.validare(obj);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }
    obj.setID(4);
    try
    {
        validator.validare(obj);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }
    obj.setName("Gabi");
    try
    {
        validator.validare(obj);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }
    obj.setType("Mare");
    try
    {
        validator.validare(obj);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }
}

void runRepositoryAparts()
{
    RepoAparts repo;
    repo.adauga(Apartment(5, "asd", "asd", 50));
    try
    {
        repo.adauga(Apartment(5));
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    assert(repo.getSize() == 1);
    assert(repo.getElems() == std::vector<Apartment>{Apartment(5, "asd", "asd", 50)});
    repo.adauga(Apartment(20, "xyz", "xyz", 100));
    assert(repo.cautare(Apartment(6)) == -1);
    assert(repo.cautare(Apartment(5)) == 5);
    assert(repo.cautare(Apartment(20, "ss", "ss", 200)) == 20);

    try
    {
        repo.modifica(Apartment(99));
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    repo.modifica(Apartment(5, "ppp", "ppp", 457));
    assert((repo.getElems()).at(0).getID() == 5);
    assert((repo.getElems()).at(0).getName() == "ppp");
    assert((repo.getElems()).at(0).getType() == "ppp");
    assert((repo.getElems()).at(0).getSurface() == 457);

    try
    {
        repo.sterge(Apartment(99));
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    repo.sterge(Apartment(5));
    assert(repo.getElems() == std::vector<Apartment>{Apartment(20, "xyz", "xyz", 100)});
}

void runServiceAparts()
{
    RepoAparts repoAparts;
    Validator validator;
    ServiceAparts service{ repoAparts, validator };
    service.adauga(5, "asd", "asd", 50);
    service.modifica(5, "x", "x", 60);
    service.sterge(5);
    try
    {
        service.undo();
        service.undo();
        service.undo();
        assert(true);
    }
    catch (const ServiceException)
    {
        assert(false);
    }
    try
    {
        service.undo();
        assert(false);
    }
    catch (const ServiceException)
    {
        assert(true);
    }
    service.adauga(5, "asd", "asd", 50);
    assert(service.getElems() == std::vector<Apartment>{Apartment(5, "asd", "asd", 50)});
    try
    {
        service.adauga(-1, "xx", "xx", 16);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }

    service.adauga(20, "xyz", "xyz", 100);
    try
    {
        service.cauta(6);
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    try
    {
        service.cauta(5);
        assert(true);
    }
    catch (RepoException)
    {
        assert(false);
    }
    assert(service.cauta(20) == 0);
    try
    {
        service.cauta(-7);
        assert(false);
    }
    catch (ValidException)
    {
        assert(true);
    }
    assert(service.suma() == 150);
    service.modifica(5, "ppp", "ppp", 457);
    assert((service.getElems()).at(0).getID() == 5);
    assert((service.getElems()).at(0).getName() == "ppp");
    assert((service.getElems()).at(0).getType() == "ppp");
    assert((service.getElems()).at(0).getSurface() == 457);

    service.sterge(5);
    assert(service.getElems() == std::vector<Apartment>{Apartment(20, "xyz", "xyz", 100)});

    service.adauga(18, "a", "xy", 10);
    service.adauga(25, "b", "xyz", 59);
    service.adauga(93, "a", "zxy", 1017);
    service.adauga(59, "a", "xy", 59);
    std::string type{ "xyz" };
    std::vector <Apartment>* vector;
    vector = service.filtrare([](const Apartment& obj, void* type) ->bool {return obj.getType() == *(std::string*)type; }, &type);
    assert((*vector).at(0).getID() == 20);
    assert((*vector).at(1).getID() == 25);
    delete vector;

    int surface{ 59 };
    vector = service.filtrare([](const Apartment& obj, void* surface) ->bool {return obj.getSurface() == *(int*)surface; }, &surface);
    assert((*vector).at(0).getID() == 25);
    assert((*vector).at(1).getID() == 59);
    delete vector;

    service.sterge(20);
    service.sterge(18);
    service.sterge(25);
    service.sterge(93);
    service.sterge(59);

    service.adauga(5, "asd", "asd", 100);
    service.adauga(10, "vaf", "vaf", 50);
    vector = service.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getSurface() < obj2.getSurface(); });
    assert((*vector).at(0).getID() == 10);
    assert((*vector).at(1).getID() == 5);
    delete vector;

    service.adauga(12, "bca", "bca", 400);
    vector = service.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool {return obj1.getName().compare(obj2.getName()) < 0; });
    assert((*vector).at(0).getID() == 5);
    assert((*vector).at(1).getID() == 12);
    assert((*vector).at(2).getID() == 10);
    delete vector;

    service.sterge(5);
    service.sterge(10);
    service.sterge(12);
    service.adauga(9, "cad", "cad", 100);
    service.adauga(12, "posta", "posta", 400);
    service.adauga(19, "cad", "cad", 50);
    vector = service.sortare([](const Apartment& obj1, const Apartment& obj2) ->bool { if (obj1.getType().compare(obj2.getType()) < 0) return true;  if (obj1.getSurface() < obj2.getSurface()) return true; return false; });
    assert((*vector).at(0).getID() == 19);
    assert((*vector).at(1).getID() == 9);
    assert((*vector).at(2).getID() == 12);
    delete vector;

    delete service.getDTO();
    EntityCountDTO ecd;
    assert(ecd.getCount() == 0);
    assert(ecd.getName() == "");
    assert(ecd.getType() == "");
}

void runServiceList()
{
    RepoAparts repoAparts;
    RepoAparts repoList;
    Validator validator;
    ServiceList service{ repoAparts, repoList, validator };
    try
    {
        service.undoCos();
        assert(false);
    }
    catch (ServiceException)
    {
        assert(true);
    }
    repoAparts.adauga(Apartment(5));
    service.adauga(5);
    assert(service.getSize() == 1);
    service.undoCos();
    assert(service.getSize() == 0);
    try
    {
        service.adauga(99);
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    service.adauga(5);
    try
    {
        service.adauga(5);
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
    assert(service.getSize() == 1);
    repoAparts.adauga(Apartment(99));
    repoAparts.adauga(Apartment(444));
    repoAparts.adauga(Apartment(22));
    service.genereaza(2);
    assert(service.getSize() == 3);
    service.genereaza(4);
    assert(service.getSize() == 4);
    service.sterge();
    auto el = service.getElems();
    try
    {
        service.genereaza(-1);
        assert(false);
    }
    catch (RepoException)
    {
        assert(true);
    }
}

void runExport()
{
    RepoAparts repoAparts;
    RepoAparts repoList;
    Validator validator;
    ServiceList service(repoAparts, repoList, validator);
    repoAparts.adauga(Apartment(5, "a", "a", 10));
    repoAparts.adauga(Apartment(7, "b", "b", 20));
    repoAparts.adauga(Apartment(12, "f", "f", 30));
    service.adauga(5);
    service.adauga(12);
    service.Export("testHTML.html");
    service.Export("testCSV.csv");
}

void runRepoFile()
{
    RepoFile repo("repoTEST.txt");
    repo.adauga(Apartment(7, "s", "s", 123));
    repo.adauga(Apartment(19, "xyz", "asd", 444));
    try
    {
        repo.adauga(Apartment(19));
        assert(false);
    }
    catch (const RepoException)
    {
        assert(true);
    }
    try
    {
        repo.modifica(Apartment(9));
        assert(false);
    }
    catch (const RepoException)
    {
        assert(true);
    }
    try
    {
        repo.sterge(Apartment(9));
        assert(false);
    }
    catch (const RepoException)
    {
        assert(true);
    }
    assert(repo.getSize() == 3);
    assert(repo.getApart(7) == Apartment(7));
    repo.modifica(Apartment(7, "d", "d", 44));
    repo.sterge(Apartment(7));
    std::ofstream ofs;
    ofs.open("repoTEST.txt", std::ofstream::out | std::ofstream::trunc);
    std::ofstream fout("repoTEST.txt");
    fout << 99 << std::endl << "Gigi" << std::endl << "Becali" << std::endl << 2000 << std::endl;
    try
    {
        RepoFile repoB("asd/xyz.txt");
        assert(false);
    }
    catch (const RepoException)
    {
        assert(true);
    }
}

void runRepoLab()
{
    RepoLab repo(0.3);
    while (true) {
        try { repo.adauga(Apartment(5));	break; }
        catch (const ChaosException) {}
    }
    assert(repo.getApart(5) == Apartment(5));
    while (true) {
        try { repo.adauga(Apartment(5));	break; }
        catch (const ChaosException) {}
        catch (const RepoException) { assert(true); break; }
    }
    while (true) {
        try { repo.modifica(Apartment(5, "t", "t", 100));	break; }
        catch (const ChaosException) {}
    }
    assert(repo.getElems().at(0) == Apartment(5));
    while (true) {
        try { repo.cautare(Apartment(5, "t", "t", 100));	break; }
        catch (const ChaosException) {}
    }
    assert(repo.getSize() == 1);
    while (true) {
        try { repo.sterge(Apartment(5));	break; }
        catch (const ChaosException) {}
    }
    while (true) {
        try { repo.sterge(Apartment(5));	break; }
        catch (const ChaosException) {}
        catch (const RepoException) { assert(true); break; }
    }
    while (true) {
        try { repo.modifica(Apartment(5));	break; }
        catch (const ChaosException) {}
        catch (const RepoException) { assert(true); break; }
    }
}

void runTests()
{
    runDomain();
    runValidator();
    runRepositoryAparts();
    runServiceAparts();
    runServiceList();
    runExport();
    runRepoFile();
    runRepoLab();
}
