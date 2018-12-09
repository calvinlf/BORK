//
// Created by CalPC on 11/27/2018.
//

#include "Character.h"
#include "Die.h"
#include "Dishes.h"
#include "Flier.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

Character::Character() {
    currentRoom = 0;
    makeMap();
    theMap.at(0).addItem(new Flier());
    theMap.at(1).addItem(new Die());
    theMap.at(1).addItem(new Dishes());
}

void Character::makeMap() {
    string line = "";
    int roomNum = 0;
    string input = "";
    ifstream mapText("C:\\Users\\CalPC\\Projects\\BORK\\theMap.txt");
    if (mapText.is_open()) {
        while (line != "STOP") {
            getline(mapText,line);
            istringstream phrase(line);
            phrase >> input;
            if (input == "room") {
                //cout << "r ";
                phrase >> roomNum;
                string namesStr = "";
                getline(mapText, namesStr);
                vector<string> names = makeVectorForMap(namesStr);
                string description;
                getline(mapText, description);
                theMap.push_back(Room(names, description));
            } else if (input == "e") {
                //cout << "e ";
                int address = 0;
                phrase >> address;
                string pathsStr;
                phrase >> pathsStr;
                vector<string> paths = makeVectorForMap(pathsStr);
                theMap.at(roomNum).addExit(paths, address);
            } else if (input == "i") {
                //cout << "i ";
                string namesStr = "";
                phrase >> namesStr;
                for (unsigned int i = 0; i < namesStr.size(); i++) {
                    if (namesStr[i] == '.') {
                        namesStr[i] = ' ';
                    }
                }
                vector<string> names = makeVectorForMap(namesStr);
                string description = "";
                string nextWord = "";
                phrase >> nextWord;
                while (nextWord != "*") {
                    description += nextWord + " ";
                    phrase >> nextWord;
                }
                string use = "";
                nextWord = "";
                phrase >> nextWord;
                while (nextWord != "*") {
                    use += nextWord + " ";
                    phrase >> nextWord;
                }
                string verbStr = "";
                phrase >> verbStr;
                vector<string> verbs = makeVectorForMap(verbStr);
                int weight = 0;
                phrase >> weight;
                theMap.at(roomNum).addItem(new Item(names, description, use, verbs, weight));
            }
        }
        mapText.close();
    } else cout << "Unable to open file";
    srand(time(NULL));
    for (int i = 0; i < NUM_PENNIES; i++){
        theMap.at(rand() % theMap.size()).addItem(new Item({"penny", "coin"}, "Abe's a bit scratched, but still worth 1 cent.", "It's not really worth anything, maybe if you find a lot of them, sorry", {"spend", "trade"}));
    }
}

vector<string> Character::makeVectorForMap(string namesStr) {
    //cout << "> ";
    vector<string> names;
    if (namesStr.find('>') == string::npos) {
        names.push_back(namesStr);
    }
    while (namesStr.find('>') != string::npos) {
        string nextName = namesStr.substr(0, namesStr.find('>'));
        names.push_back(nextName);
        namesStr = namesStr.substr(namesStr.find('>') + 1, namesStr.size());
        if (namesStr.find('>') == string::npos) {
            names.push_back(namesStr);
        }
    }
    return names;
}

int Character::cleanUp() {
    for (unsigned int i = 0; i < yourItems.size(); i++) {
        delete yourItems.at(i);
    }
    for (unsigned int i = 0; i < theMap.size(); i++) {
        theMap.at(i).deleteItems();
    }
    return 0;
}

void Character::describeCurrentRoom() {
    cout << theMap.at(currentRoom).getRoomDescription() << endl;
}

bool Character::hasItem(string itemName) {
    for (unsigned int i = 0; i <  yourItems.size(); i++) {
        if (yourItems.at(i)->hasName(itemName)) return true;
    }
    return false;
}

Item* Character::getItem(string itemName) {                    // memory leak waiting to happen...
    for (unsigned int i = 0; i <  yourItems.size(); i++) {
        if (yourItems.at(i)->hasName(itemName)) {
            return yourItems.at(i);
        }
    }
    return new Item({"nada"},"","",{});
}

void Character::removeItem(string itemName) {
    for(unsigned int i = 0; i < yourItems.size(); i++) {
        if (yourItems.at(i)->hasName(itemName)) {
            yourItems.erase(yourItems.begin() + i);
            i = yourItems.size();
        }
    }
}

string Character::getNameFromVerb(string verb) {
    for (unsigned int i = 0; i <  yourItems.size(); i++) {
        if (yourItems.at(i)->hasUsePhrase(verb)) {
            return yourItems.at(i)->getName();
        }
    }
    return "";
}

bool Character::hasItemWithName(string name) {
    Item* tempPtr = getItem(name);
    if (tempPtr->getName() == "nada") {
        delete tempPtr;
        return false;
    }
    return true;
}

void Character::checkIt(string input, string output) {
    istringstream phrase(input);
    string firstWord = "";
    phrase >> firstWord;
    if (input.substr(input.find(' ') + 1) == "it") {
        cout << "What \"it\" are you talking about?" << endl;
        string it = "";
        getline(cin, it);
        act(firstWord + " " + it);
    } else {
        cout << output << endl;
    }
}

int Character::numPenniesYouHave() {
    int numPennies = 0;
    for (unsigned int i = 0; i < theMap.at(currentRoom).getRoomItems().size(); i++) {
        if (theMap.at(currentRoom).getRoomItems().at(i)->getName() == "penny") {
            numPennies++;
        }
    }
    return numPennies;
}

void Character::act(string input) {
    istringstream phrase(input);
    string firstWord = "";
    phrase >> firstWord;
    string afterFirstWord = input.substr(input.find(' ') + 1);
    if (firstWord == "look" || firstWord == "where") {
        describeCurrentRoom();
    } else if (firstWord == "hello" || firstWord == "hi" || firstWord == "hey") {
        cout << "Hi" << endl;
    } else if (firstWord == "let's" || firstWord == "lets") {
        act(afterFirstWord);
    } else if (firstWord == "thank" || firstWord == "thanks") {
        cout << "Your welcome!" << endl;
    } else if (firstWord == "yes" || firstWord == "no" || firstWord == "maybe") {
        cout << "Maybe" << endl;
    } else if (firstWord == "quit") {
        cout << "Come again soon!" << endl;
    } else if (firstWord == "talk") {
        cout << "\"blah\"" << endl;
    } else if (firstWord == "jump") {
        cout << "You jump. yay." << endl;
    } else if (firstWord == "sleep") {
        if (currentRoom == 0) {
            cout << "You awake" << endl;
        } else {
            cout << "It's not nap time yet! Go back to your room to sleep." << endl;
        }
    } else if (firstWord == "ok" || firstWord == "okay") {
        cout << "Okay!" << endl;
    } else if (firstWord == "sing") {
        cout << "\"La La La\", now go do something useful." << endl;
    } else if (firstWord == "help" || firstWord == "what") {
        cout << "Try to \"examine\" things or \"go\" directions. Don't worry, you are smart!" << endl;
    } else if (find(cardinalDirectionList, input) >= 0) {
        int newRoom = theMap.at(currentRoom).exit(input);
        if (newRoom < 0 ) {
            cout << "You can't go there" << endl;
        } else {
            currentRoom = newRoom;
            cout << "You have Traveled" << endl;
            cout << theMap.at(currentRoom).getRoomDescription() << endl;
        }
    } else if (firstWord == input) {                                                   //ONE WORD THINGS BEFORE THIS POINT
        cout << firstWord << " what?" << endl;
        string what = "";
        getline(cin, what);
        act(input + " " + what);                                                       //TWO WORD THINGS AFTER THIS POINT
    } else if (firstWord == "pick") {
        act(afterFirstWord);
    } else if (firstWord == "take" || firstWord == "grab" || firstWord == "snatch" || firstWord == "get" || firstWord == "up") {
        string whatToTake = afterFirstWord;
        if (theMap.at(currentRoom).hasItem(whatToTake)) {
            if (theMap.at(currentRoom).getItem(whatToTake)->getWeight() <= carryCapacity) {
                yourItems.push_back(theMap.at(currentRoom).getItem(whatToTake));
                cout << "You have the " << theMap.at(currentRoom).getItem(whatToTake)->getName() << "!" << endl;
                theMap.at(currentRoom).removeItem(whatToTake);
                carryCapacity -= theMap.at(currentRoom).getItem(whatToTake)->getWeight();
            } else {
                cout << "That is too heavy to hold. You can try to \"drop\" stuff to make more room." << endl;
            }
        } else {
            checkIt(input, "Item not here.");
        }
    } else if (firstWord == "drop" || firstWord == "leave") {
        string whatToDrop = afterFirstWord;
        if (hasItem(whatToDrop)) {
            theMap.at(currentRoom).addItem(getItem(whatToDrop));
            carryCapacity += theMap.at(currentRoom).getItem(whatToDrop)->getWeight();
            cout << "You drop the " << theMap.at(currentRoom).getItem(whatToDrop)->getName() << "!" << endl;
            removeItem(whatToDrop);
            if (currentRoom == 0 && numPenniesYouHave() == NUM_PENNIES) {
                cout << "YOU WIN!!!!" << endl;
            }
        } else {
            checkIt(input, "You don't have that item.");
        }
    } else if (firstWord == "examine" || firstWord == "inspect" || firstWord == "analyze") {
        string whatToExamine = input.substr(input.find(' ') + 1);
        if (whatToExamine == "yourself" || whatToExamine == "me" || whatToExamine == "myself" || whatToExamine == "self") {
            cout << "Why, you look fantastic!" << endl;
            cout << "You have:" << endl;
            if (yourItems.empty()) cout << "Nothing :(" << endl;
            for (unsigned int i = 0; i < yourItems.size(); i++) {
                cout << "  " << i + 1 << ". " << yourItems.at(i)->getName() << endl;
            }
        } else if (theMap.at(currentRoom).hasName(whatToExamine)) {
            describeCurrentRoom();
            cout << "The area has:" << endl;
            if (theMap.at(currentRoom).getRoomItems().empty()) {cout << "Nothing :(" << endl;}
            for (unsigned int i = 0; i < theMap.at(currentRoom).getRoomItems().size(); i++) {
                cout << "  " << i + 1 << ". " << theMap.at(currentRoom).getRoomItems().at(i)->getName() << endl;
            }
        } else if (theMap.at(currentRoom).hasItem(whatToExamine)){
            cout << theMap.at(currentRoom).getItem(whatToExamine)->getDescription() << endl;
        } else if (hasItem(whatToExamine)){
            cout << getItem(whatToExamine)->getDescription() << endl;
        } else {
            checkIt(input, "You can't " + firstWord + " that.");
        }
    } else if (firstWord == "go" || firstWord == "walk" || firstWord == "run") {
        string whereToGo = input.substr(input.find(' ') + 1);
        int newRoom = theMap.at(currentRoom).exit(whereToGo);
        if (newRoom < 0 ) {
            cout << "You can't " << firstWord << " there" << endl;
        } else {
            currentRoom = newRoom;
            cout << "You have Traveled" << endl;
            cout << theMap.at(currentRoom).getRoomDescription() << endl;
        }
    } else if (!getNameFromVerb(firstWord).empty()) {
        string directObject = input.substr(input.find(' ') + 1);
        if (hasItemWithName(directObject)) {
            getItem(directObject)->useItem();
        }  else {
            checkIt(input, "You can't " + firstWord + " that.");
        }
    } else {
        cout << "You don't know how to do that, sorry, try again." << endl;
    }
}
