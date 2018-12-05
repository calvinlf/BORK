//
// Created by CalPC on 11/27/2018.
//

#ifndef BORK_CHARACTER_H
#define BORK_CHARACTER_H

#include "Item.h"
#include "Room.h"
#include <vector>
#include <string>
using namespace std;

class Character {
public:
    Character();
    void act(string input);
    int cleanUp();
private:
    unsigned int currentRoom;
    vector<Item*> yourItems;
    vector<Room> theMap;
    void describeCurrentRoom();
    bool hasItem(string itemName);
    Item* getItem(string itemName);
    void removeItem(string itemName);
    string getNameFromVerb(string verb);
    bool hasItemWithName(string name);
    void checkIt(string input, string output);
    int numPenniesYouHave();
    void makeMap();
    vector<string> makeVectorForMap(string namesStr);
    const int NUM_PENNIES = 3;
    vector<string> cardinalDirectionList = {"N", "S", "E", "W", "NE", "SE", "NW", "SW", "U", "D"};
    template<typename theType> int find(vector<theType> list, theType whatToFind) {
        for (unsigned int i = 0; i < list.size(); i++) {
            if (list.at(i) == whatToFind) return i;
        }
        return -1;
    }
    int carryCapacity = 50;
};


#endif //BORK_CHARACTER_H
