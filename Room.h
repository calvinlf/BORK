//
// Created by CalPC on 11/27/2018.
//

#ifndef BORK_ROOM_H
#define BORK_ROOM_H

#include <string>
#include <vector>
#include <map>
#include "Item.h"
using namespace std;

class Room {
public:
    Room(string roomDescription);
    Room(vector<string> names, string roomDescription);
    string getRoomDescription();
    void addItem(Item* newItem);
    void removeItem(string itemName);
    bool hasItem(string itemName);
    Item* getItem(string itemName);
    vector<Item*> getRoomItems();
    void addExit(vector<string> direction, int room);
    int exit(string direction);
    bool hasName(string name);
    void deleteItems();
private:
    string roomDescription;
    vector<Item*> roomItems;
    map<string, int> exits;
    vector<string> names;
    const vector<string> BASIC_NAMES = {"area", "the area", "my location", "where I am"};
};


#endif //BORK_ROOM_H
