//
// Created by CalPC on 11/27/2018.
//

#include "Item.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Item::Item() {
    this->names = {"basic"};
    this->description = "Basic";
    this->use = "basics";
    this->usePhrases = {"use"};
}

Item::Item(vector<string> names, string description, string use, vector<string> usePhrases) {
    this->names = names;
    this->description = description;
    this->use = use;
    this->usePhrases = usePhrases;
    addTheToNames(names);
}

Item::Item(vector<string> names, string description, string use, vector<string> usePhrases, int weight) {
    this->names = names;
    this->description = description;
    this->use = use;
    this->usePhrases = usePhrases;
    this->weight = weight;
    addTheToNames(names);
}

void Item::addTheToNames(vector<string> names){
    for (unsigned int i = 0; i < names.size(); i++) {
        this->names.push_back("the " + names.at(i));
    }
}

bool Item::hasName(string name) {
    for (unsigned int i = 0; i < names.size(); i++) {
        if (names.at(i) == name) return true;
    }
    return false;
}

string Item::getName() {
    return names.at(0);
}

string Item::getDescription() {
    return description;
}

string Item::getUse() {
    return use;
}

bool Item::hasUsePhrase(string phrase) {
    for (unsigned int i = 0; i < usePhrases.size(); i++) {
        if (usePhrases.at(i) == phrase) return true;
    }
    return false;
}

void Item::useItem() {
    cout << use << endl;
}