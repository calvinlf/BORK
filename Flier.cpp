//
// Created by CalPC on 12/5/2018.
//

#include "Flier.h"
#include <string>

Flier::Flier() {
    this->names = {"leaflet", "flier", "paper"};
    this->description = "Welcome to BORK!\n"
                        "BORK is a game of adventure, danger, and low cunning. In it you will explore some of the most amazing territory ever seen by mortals. No computer should be without one!\"\n"
                        "Type \"quit\" when you are done to exit the game.\n"
                        "You've go this!";
    this->use = description;
    this->usePhrases = {"read", "roll", "toss"};
    addTheToNames(names);
}