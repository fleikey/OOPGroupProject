#ifndef DORMITORY_H
#define DORMITORY_H
#include <vector>
#include "Room.h"
#include "Student.h"

class Dormitory {
private:
    std::vector<Room> rooms;
    string name;
public:
    Dormitory(string name);
    void addRoom(const Room& room);
    Room* findAvailableRoom();
    void assignStudentToRoom(Student& student);
    vector<Room>& getRooms() { return rooms; }
};
#endif
