#include "validator.h"
#include <string>


ValidException::ValidException(const std::string msg) :msg{ msg } {}

std::string ValidException::getMessage() const
{
    return this->msg;
}


int Validator::validare(const Apartment& obj) const
{
    if (obj.getID() < 0)
        throw ValidException("ID invalid.\n");
    if (obj.getName().compare("") == 0)
        throw ValidException("Nume invalid.\n");
    if (obj.getType().compare("") == 0)
        throw ValidException("Tip invalid.\n");
    if (obj.getSurface() < 0)
        throw ValidException("Suprafata invalida.\n");
    return 0;
}
