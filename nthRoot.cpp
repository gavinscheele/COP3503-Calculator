//
//  nthRoot.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "nthRoot.h"

nthRoot::nthRoot(int root, int operand, int coefficient) {
    this->type = "nthRoot";
    this->operand = operand;
    this->root = root;
    this->coefficient = coefficient;
}

nthRoot::~nthRoot() {
    
}

int* nthRoot::primeFactorization(int n) {
    int k = 0;
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
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
    //if coefficient == 0 then return 0?
    int* factorsArray = primeFactorization(operand);
    int i = 0;
    while (i <= factors.size()) {
        int j = i;
        int count = 0;
        while (j <= factors.size() && factors[j + 1] == factors[j]) {
            count++;
            j++;
        }
        if (count >= root) {
            coefficient *= (factors[i] ^ (count/root)); 
            operand = operand / (factors[i] ^ (count - (count % root))); 
        }
        i = j + 1;
    }
    if (operand == 1) {
        Integer newInt = new Integer(coefficient);
        return newInt;
    }
    else {
        Expression* newRoot = new nthRoot(root, operand, coefficient);
        delete this;  //is this necessary?
        return newRoot;
    }
    
}


Expression* nthRoot::add(Expression* a) {
    nthRoot *b = (nthRoot *)a;
    int asCoefficient = b->getCoefficient(); 
    int asOperand = b->getOperand();
    int asRoot = b->getRoot();
    if (root == asRoot && operand == asOperand) {
        int newCoefficient = asCoefficient + coefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        return newNthRoot;
    }
    else {
        return this;
    }
    
}

Expression* nthRoot::subtract(Expression* a) {
    nthRoot *b = (nthRoot *)a;
    int asCoefficient = b->getCoefficient(); 
    int asOperand = b->getOperand();
    int asRoot = b->getRoot();
    if (root == asRoot && operand == asOperand) {
        int newCoefficient = coefficient - asCoefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        return newNthRoot;
    }
    else {
        return this;
    }
}

Expression* nthRoot::multiply(Expression* a) {
    nthRoot *b = (nthRoot *)a;                      
    int asCoefficient = b->getCoefficient();
    int asOperand = b->getOperand();
    int asRoot = b->getRoot();
    if (root == asRoot) {
        int newCoefficient = asCoefficient * coefficient;
        int newOperand = operand * asOperand;       //asOperand doesnt exist?
        nthRoot* newNthRoot = new nthRoot(root, newOperand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplified Version;
    }
    else {
        return this;
    }
}

Expression* nthRoot::divide(Expression* a) {
    nthRoot *b = (nthRoot *)a;                  
    int asRoot = b->getRoot();
    int asOperand = b->getOperand();
    int asCoefficient = b->getCoefficient();
    if (root == asRoot) {
        int newCoefficient = coefficient / asCoefficient;
        int newOperand = operand / asOperand;
        nthRoot* newNthRoot = new nthRoot(root, newOperand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
    else {
        return this;
    }
}

int nthRoot::getRoot() {
    return root;
}

int nthRoot::getOperand() {
    return operand;
}

int nthRoot::getCoefficient() {
    return coefficient;
}

void nthRoot::setCoefficient(int n) {
    this->coefficient = n;
}

void nthRoot::setOperand(int n) {
    this->operand = n;
}

void nthRoot::setRoot(int n) {
    this->root = n;
}
ostream& nthRoot::print(std::ostream& output) const {
    output << this->coefficient  << "*" << this->root << "rt:" << this->operand;    
    return output;
}

string nthRoot::toString() {
    stringstream s; 
    s << coefficient << "*" << root << "rt:" << operand;
    return s.str();
}
