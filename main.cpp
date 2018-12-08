/*
 * Made by Calvin Fischer
 *
 */

#include <iostream>
#include <string>
#include <functional>
#include "Room.h"
#include "Character.h"
using namespace std;


int main() {
    cout << "*********************Welcome to BORK*********************" << endl;
    cout << "A BYU simulation designed mostly to teach people" << endl;
    cout << "cardinal directions (and also to have fun doing it)."  << endl;
    cout << "Only use capital letters for single letter directions." << endl;
    cout << "There are lots of things to explore and do!" << "\n\n\n";

    Character you;
    string input = "";

    cout << "You Awake" << endl;
    cout << "You see a leaflet on the ground." << endl;
    while (input != "quit") {
        cout << "->";
        getline(cin, input);
        you.act(input);
    }

    return you.cleanUp();
}

