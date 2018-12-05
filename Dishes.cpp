//
// Created by CalPC on 12/3/2018.
//

#include "Dishes.h"
#include <iostream>
#include <string>

Dishes::Dishes(){
    this->names = {"dirty dishes", "dishes"};
    this->description = "Dirty dishes- why on earth did you pick these up?";
    this->use = "You clean the dishes! What a great roommate you are!";
    this->usePhrases = {"clean", "wash"};
    weight = 15;
    addTheToNames(names);
}

void Dishes::useItem() {
    if (isClean) {
        cout << use << endl;
    } else {
        cout << "You clean the dishes! What a great roommate you are!" << endl;
        use  = "They are already clean...";
        names = {"clean dishes", "dishes"};
        addTheToNames(names);
        description = "They are spotlessly clean dishes, undeniably cleaned by some hero of the kitchen.";
    }
}