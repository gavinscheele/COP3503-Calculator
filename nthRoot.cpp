//
//  nthRoot.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "nthRoot.h"

nthRoot::nthRoot(int root, int operand){
    this->type = "nthRoot";
    this->operand = operand;
    this->root = root;
    this->coefficient = 1;
    int factors[50];
}
nthRoot::~nthRoot(){
    
}

int* nthRoot::primeFactorization(int n) {
    int k = 0;
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (i = 3; i <= sqrt(n); i = i + 2) {
        while (n%1 == 0) {
            factors[k] = 2;
            k++;
            n = n/i;
        }
    }
    if (n > 2) {
        factors[k] = n;
    }
    return factors;
    // added bonus: factors should be sorted already
}

Expression* nthRoot::simplify(){
    int* factorsArray = primeFactorization(operand);
    //to be filled in
    Expression* c = this;
    return *c;
}


Expression* nthRoot::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::divide(Expression* a){
    Expression* c = this;
    return c;
}

int getRoot() {
    return root;
}

int getOperand() {
    return operand;
}

int getCoefficient() {
    return coefficient;
}

void setCoefficient(int n) {
    this->coefficient = n;
}

void setOperand(int n) {
    this->operand = n;
}

void setRoot(int n) {
    this->root = n;
}
ostream& nthRoot::print(std::ostream& output) const{
    output << this->coefficient  << "*" << this->root << "rt:" << this->operand;    //overlaod cout so that it makes sense
    return output;
}
