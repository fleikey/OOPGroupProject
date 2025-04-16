#include "Person.h"
#include <iostream>

Person::Person(const string &name) : name(name) {}

string Person::getName() const
{
    return name;
}
