#include "Room.h"
Room::Room(int num) : number(num), occupied(false) {}
void Room::assignStudent(Student& student)
 { occupied = true; }
bool Room::isAvailable() const
 { return !occupied; }
int Room::getNumber() const
 { return number; }
