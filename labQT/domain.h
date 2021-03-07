#pragma once
#include <string>

class Apartment
{
private:

    int ID = 0, surface = 0;
    std::string name, type;


public:

    Apartment() = default;

    /*constructor fara parametri
    initializeaza ID-ul si surface-ul cu 1, iar name si type le face vide*/
    Apartment(const int ID);

    /*constructor general
    initializeaza parametri cu valorile date de utilizator*/
    Apartment(const int ID, const std::string name, const std::string type, const int surface);

    /*functie de copiere*/
    Apartment(const Apartment& other);

    /*in: -
    functie de getter pentru ID
    out: ID*/
    int getID() const noexcept;

    /*in: -
    functie de getter pentru nume
    out: name*/
    std::string getName() const;

    /*in: -
    functie de getter pentru tip
    out: type*/
    std::string getType() const;

    /*in: -
    functie de getter pentru suprafata
    out: surface*/
    int getSurface() const noexcept;

    /*in: ID - ID nou
    functie de setter pentru ID
    out: -*/
    void setID(const int ID) noexcept;

    /*in: name - nume nou
    functie de setter pentru nume
    out: -*/
    void setName(const std::string name);

    /*in: type - tip nou
    functie de setter pentru tip
    out: -*/
    void setType(const std::string type);

    /*in: surface - suprafata noua
    functie de setter pentru suprafata
    out: -*/
    void setSurface(const int surface) noexcept;

    /*functie de supraincarcare a operatorului ==*/
    bool operator==(const Apartment& other) const noexcept;
};
