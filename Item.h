//
// Created by CalPC on 11/27/2018.
//

#ifndef BORK_ITEM_H
#define BORK_ITEM_H
#include <string>
#include <vector>
#include <functional>
using namespace std;

class Item {
public:
    Item();
    Item(vector<string> names, string description, string use, vector<string> usePhrases);
    Item(vector<string> names, string description, string use, vector<string> usePhrases, int weight);
    bool hasName(string name);
    string getName();
    string getDescription();
    string getUse();
    virtual void useItem();
    bool hasUsePhrase(string phrase);
    int getWeight() {return weight;}
protected:
    void addTheToNames(vector<string> names);
    vector<string> names;
    vector<string> usePhrases;
    string description;
    string use;
    int weight = 1;
};


#endif //BORK_ITEM_H
