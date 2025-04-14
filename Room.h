#ifndef ROOM_H
#define ROOM_H
class Room {
private:
    int number;
    bool occupied;
public:
    Room(int number);
    void assignStudent(Student& student);
    bool isAvailable() const;
    int getNumber() const;
};
#endif
