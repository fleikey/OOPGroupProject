#ifndef DORMITORY_H
#define DORMITORY_H
#include <vector>
#include "Room.h"
#include "Student.h"

class Dormitory {
private:
    std::vector<Room> rooms;
public:
    void addRoom(const Room& room);
    Room* findAvailableRoom();
    void assignStudentToRoom(Student& student);
};
#endif
