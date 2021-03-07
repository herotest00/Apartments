#pragma once
#include "domain.h"


class ValidException
{
private:
    std::string msg;

public:
    ValidException(const std::string msg);

    std::string getMessage() const;
};



class Validator
{
public:

    /*in: obj - obiect de tip apartament
    functie care valideaza atributele obiectului
    out: -
    raises: ValidException - daca atributele sunt invalide*/
    int validare(const Apartment& obj) const;
};
