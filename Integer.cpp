//
//  Integer.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/28/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Integer.h"
Integer::Integer(int value){
    this->type = "integer";
    this->value = value;
}
Integer::~Integer(){

}
int Integer::getValue() {
    return value;
}
void Integer::setValue(int n) {
    value = n;
}
Expression* Integer::add(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value+=b->getValue;

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        b->setNumerator(b->getNumerator->add(this->multiply(b->getDenominator)));
        this = b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::subtract(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value-=b->getValue;

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        b->setNumerator(b->getNumerator->subtract(this->multiply(b->getDenominator)));
        this = b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::multiply(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value*=b->getValue;

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        b->setNumerator(b->getNumerator->multiply(this));
        this = b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::divide(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value/=b->getValue;

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        b->setDenominator(b->getDenominator->multiply(this));
        this = b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
ostream& Integer::print(std::ostream& output) const{
    output << this->value;
    return output;
}

string Integer::toString() {
    string str = (string) value;
    return str;
}
