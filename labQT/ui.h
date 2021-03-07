#pragma once
#include "service.h"
#include <iostream>

class UI {

private:

    ServiceAparts& serviceAparts;
    ServiceList& serviceList;

public:

    UI(ServiceAparts& serviceAparts, ServiceList& serviceList) noexcept : serviceAparts{ serviceAparts }, serviceList{ serviceList } {};

    void afisare(const std::vector<Apartment> vector) const;

    void afisareCount() const;

    std::string readString(const std::string message) const;

    int readInt(const std::string message) const;

    void adaugaAparts();

    void modificaAparts();

    void stergeAparts();

    void cautaAparts();

    void filtrareAparts();

    void sortareAparts();

    void adaugaList();

    void stergeList();

    void genereazaList();

    void Export();

    void undo();

    void undoCos();

    void menu0();

    void menu1();

    void menu2();

    void run();
};
