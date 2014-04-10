//
//  Exponent.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Exponential.h"


Exponential::Exponential(Expression* base, Rational* exponent){
    this->type = "exponential";
    this->base = base;
    this->exponent = exponent;
    Integer *exde = (Integer *)exponent->getDenominator();
    if (exde->getValue() != 1) {
        base = nthRoot(exde, base);
        exponent = exponent->getNumerator();
    }
    Integer *exnu = (Integer *)exponent->getNumerator();
    if (canExponentiate()) {
    this = exponentiate();
    }
}
Exponential::~Exponential(){

}

bool Exponential::canExponentiate() {
    if(base->type == "euler"){
        return false;

    }else if(base->type == "exponential"){
	Exponential* ex = (exponential *) base;
	this->exponent *= ex->getExponent();
	ex->setExponent(1);			// may need to be corrected because exponent is not an int
        return false;			// false is returned because the base itself would have already been exponentiated if it were possible

    }else if(base->type == "integer"){
        return true;
        

    }else if(base->type == "logarithm"){
        return false;

    }else if(base->type == "nthRoot"){
	nthRoot* nr = (nthRoot *) base;
	Rational* r = new Rational(this->exponent, nr->getRoot());
	this->exponent = r;
	nr->setRoot()=1;

    }else if(base->type == "pi"){
        return false;

    }else if(base->type == "rational"){
        Rational* r = (rational *) base;
        if (r->getNumerator->type == "integer") {
          // numerator is an integer, more code goes here 
        } 
        if (r->getDenominator->type == "integer") {
            // denominator is an integer, more code goes here
        }

    }else{
        cout << "type not recognized" << endl;
    }
    return false;
}

Expression* Exponential::exponentiate(){
    Expression* toReturn = base;
    Expression* constantBase = base;
    if (this->exponent.getNumerator()==0) {
        Integer* ret = new Integer(1);
        return ret;
    }
    bool toFlip = false;
    if (exnu<0) {
	    exnu*=-1;
            toFlip = true;
    }
    Expression* e = this;
    for (int i = 1; i < exnu); i++) {
        toReturn*=constantBase;
    }
    exnu = 1;
    if (toFlip()) {
	Rational* r = new Rational(1, toReturn);
        return r;
    }
    return toReturn;

}

Expression* Exponential::add(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (ex->getBase()==this->base) {
		if (ex->getExponent()==this->exponent) {
			this*=2;
		}
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Exponential::subtract(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (ex->getBase()==this->base) {
		if (ex->getExponent()==this->exponent) {
			this*=0;
		}
	}
    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Exponential::multiply(Expression* a){
    /*Expression* c = this;
    if (*a == *c) //might require overriding
    {
        exponent += a->getExponent;
    }
    return c;*/
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (this->base == ex->getBase()) {
		this->exponent += ex->getExponent();
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
	Rational* r = (Rational *) r;
	r->setNumerator(r->getNumerator.multiply(this));
	this = r;
	
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Exponential::divide(Expression* a){
    /*Expression* c = this;
    if (*a == *c) //might require overriding
    {
        c->getExponent -= a->getExponent;
    }
    return c;*/
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (this->base == ex->getBase()) {
		this->exponent -= ex->getExponent();
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
	Rational* r = (Rational *) r;
	r->setDenominator(r->getDenominator.multiply(this));
	this = r;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}

Rational* Exponential::getExponent() {
    return exponent;
}

*Expression Exponential::getBase() {
    return base;
}

void Exponential::setExponent(Rational e) {
    exponent = e;
}

void Exponential::setBase(*Expression e) {
    base = e;
}

string Exponential::toString() {
    string str = base + "^" + exponent;
    return str;
}


ostream& Exponential::print(std::ostream& output) const{
    output << this->base << this->exponent; //overload cout so that it makes sense
    return output;
}
