//
// Created by CalPC on 12/1/2018.
//

#include "Die.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

Die::Die() {
    this->names = {"die", "the die", "the rolling cube", "rolling cube"};
    this->description = "A cube with black dots on it.";
    this->use = "You got a 6 and will probably continue to so.";
    this->usePhrases = {"use","roll", "toss"};
}

void Die::useItem() {
    srand(time(NULL));
    cout << "You got a " << rand() % 6 +1 << endl;
}