#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
protected:
    string name;

public:
    Person(const string &name);
    virtual void show() const = 0;
    string getName() const;
};

#endif
