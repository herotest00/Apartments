#include "domain.h"
#include <iostream>


Apartment::Apartment(const int ID)
{
    this->ID = ID;
    this->name = " ";
    this->type = " ";
    this->surface = 1;
}

Apartment::Apartment(const int ID, const std::string name, const std::string type, const int surface) :ID{ ID }, name{ name }, type{ type }, surface{ surface }{}

Apartment::Apartment(const Apartment& other) : ID{ other.getID() }, name{ other.getName() }, type{ other.getType() }, surface{ other.getSurface() } {
    //std::cout << "Copiere\n";
}

int Apartment::getID() const noexcept
{
    return this->ID;
}

std::string Apartment::getName() const
{
    return this->name;
}

std::string Apartment::getType() const
{
    return this->type;
}

int Apartment::getSurface() const noexcept
{
    return this->surface;
}

void Apartment::setID(const int param) noexcept
{
    this->ID = param;
}

void Apartment::setName(const std::string param)
{
    this->name = param;
}

void Apartment::setType(const std::string param)
{
    this->type = param;
}

void Apartment::setSurface(const int param) noexcept
{
    this->surface = param;
}

bool Apartment::operator==(const Apartment& other) const noexcept
{
    return this->ID == other.ID;
}
