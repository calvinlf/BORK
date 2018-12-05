//
// Created by CalPC on 11/27/2018.
//

#include "Room.h"
#include <vector>
using namespace std;

Room::Room(string roomDescription) {
    this->roomDescription = roomDescription;
    names = BASIC_NAMES;
}

Room::Room(vector<string> names, string roomDescription) {
    this->roomDescription = roomDescription;
    this->names = names;
    for (unsigned int i = 0; i < names.size(); i++) {
        this->names.push_back("the " + names.at(i));
    }
    for (unsigned int i = 0; i < BASIC_NAMES.size(); i++) {
        this->names.push_back(BASIC_NAMES.at(i));
    }
}

string Room::getRoomDescription() {
    return roomDescription;
}

void Room::addItem(Item* newItem) {
    roomItems.push_back(newItem);
}

void Room::removeItem(string itemName) {
    for(unsigned int i = 0; i < roomItems.size(); i++) {
        if (roomItems.at(i)->hasName(itemName)) {
            roomItems.erase(roomItems.begin() + i);
            i = roomItems.size();
        }
    }
}

bool Room::hasItem(string itemName) {
    for(unsigned int i = 0; i < roomItems.size(); i++) {
        if (roomItems.at(i)->hasName(itemName)) return true;
    }
    return false;
}

Item* Room::getItem(string itemName) {                         // this is a memory leak waiting to happen...
    for(unsigned int i = 0; i < roomItems.size(); i++) {
        if (roomItems.at(i)->hasName(itemName)) {
            return roomItems.at(i);
        }
    }
    return new Item({"nada"},"","",{});
}

vector<Item*> Room::getRoomItems() {
    return roomItems;
}

void Room::addExit(vector<string> direction, int room) {
    for (unsigned int i = 0; i < direction.size(); i ++) {
        exits.emplace(direction.at(i), room);
    }
}

int Room::exit(string direction) {
    if (exits.count(direction) == 0) return -1;
    return exits.at(direction);
}

bool Room::hasName(string name) {
    for (unsigned int i = 0; i < names.size(); i++) {
        if (names.at(i) == name) return true;
    }
    return false;
}

void Room::deleteItems() {
    for (unsigned int i = 0; i < roomItems.size(); i++) {
        delete roomItems.at(i);
    }
}