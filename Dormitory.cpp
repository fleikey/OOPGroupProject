#include "Dormitory.h"

void Dormitory::addRoom(const Room& room) {
    rooms.push_back(room);
}

Room* Dormitory::findAvailableRoom() {
    for (auto& room : rooms) {
        if (room.isAvailable()) return &room;
    }
    return nullptr;
}

void Dormitory::assignStudentToRoom(Student& student) {
    Room* availableRoom = findAvailableRoom();
    if (availableRoom) {
        availableRoom->assignStudent(student);
        student.setRoomNumber(availableRoom->getNumber());
    }
}
