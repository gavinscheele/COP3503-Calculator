//
//  main.cpp
//  Calculator
//
//  Created by Gavin Scheele on 4/6/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"
using namespace std;
int main(int argc, char * argv[])  {//a main method shouldn't have perameters - at least I don't think so. -Dan
    string choice;
    choice = "z";
    while (choice.compare("d") != 0) {
        cout << "Menu" << "\n" <<
           "a. Compute a New Expression" << "\n" <<
           "b. Help" << "\n" <<
           "c. Review Previous Expressions and Answers" << "\n" <<
           "d. Quit" << "\n";
        cin >> choice;
        cout << "\n";
        if (choice.compare("a") == 0) {
            string secondChoice = "n"
            while (secondChoice.compare("y") != 0) {
                string expression;
                cin >> expression;
                //that's the input - I don't know how you want to handle it
                cout <<"\n" << "Would you like to go back to the menu? (y/n)" << "\n";
                cin >> secondChoice;
                cout << "\n";
            }
        }
        if (choice.compare("b") == 0) {
            cout << "Directions for Use of This Program" << "\n";
        }
        if (choice.compare("c") == 0) {
            //we're screwed
        }
        else {
            cout << "Sorry, couldn't recognize your input." << "\n";        
        }
    }
    cout << "Thank You" << "\n";
    return 0;
        
}
/*
//    Rational *a = new Rational(2,1);
//    Rational *b = new Rational(1,-8);
//    Rational *c = new Rational(2,1);
//    Integer *d = new Integer(4);
//    Integer *e = new Integer(-1);
//    Integer *f = new Integer(0);
//    
//    cout << *a->add(c) << endl;
//    cout << *a->subtract(d) << endl;
//    cout << *a->multiply(e) << endl;
//    cout << *a->divide(b) << endl;
    
    Solver *s = new Solver("3 - 300");
    cout << s->solve() << endl;;
    
    
    return 0;
}
*/
