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
    this->exde = new Integer(exponent->getDenominator());
    if (exde->getValue() != 1) {
    	//if the denominator of the exponent is not 1, make the base a root of the denominator, then setting the denominator equal to 1
    	Integer* baseAsInteger = (Integer *) base;
        base = new nthRoot(exde->getValue(), baseAsInteger->getValue(), 1);
        Integer* one = new Integer(1);
        exponent->setDenominator(one);
    }
    this->exnu = new Integer(exponent->getNumerator());
    if (canExponentiate()) {
    	exponentiate();
    }
}
Exponential::~Exponential(){

}

bool Exponential::canExponentiate() {
    if(base->type == "euler"){
        return false;

    }else if(base->type == "exponential"){
	Exponential* ex = (Exponential *) base;
	this->exponent->multiply(ex->getExponent());
	Integer* numSum = new Integer (1);
	ex->getExponent()->setNumerator(numSum);
        return false;
        // false is returned because the base itself would have already been exponentiated if it were possible

    }else if(base->type == "integer"){
        return true;


    }else if(base->type == "logarithm"){
        return false;

    }else if(base->type == "nthRoot"){
	nthRoot* nr = (nthRoot *) base;
	Rational* r = new Rational(this->exponent->getNumerator(), nr->getRoot()*this->exponent->getDenominator());
	//makes a new exponent, multiplying the denominator by the root, allowing the root to be simplified to one
	this->exponent = r;
	nr->setRoot(1);
	return false;

    }else if(base->type == "pi"){
        return false;

    }else if(base->type == "rational"){
        Rational* r = (Rational *) base;
        if (r->geteNumerator()->type == "integer" && r->geteDenominator()->type == "integer") {
          Exponential* nu = new Exponential(r->geteNumerator(), this->exponent);
          r->setNumerator(nu);
          Exponential* de = new Exponential(r->geteDenominator(), this->exponent);
          r->setDenominator(de);
        }

    }else{
        cout << "type not recognized" << endl;
    }
    return false;
}

void Exponential::exponentiate(){

    Expression* constantBase = base;
    if (this->exponent->getNumerator()==0) {
        Integer* oneInt = new Integer(1);
        Rational* oneRat = new Rational(1, 1);
       this->exponent=oneRat;
       this->base=oneInt;

    }
    bool toFlip = false;
    if (exnu->getValue()<0) {
	    exnu->setValue(exnu->getValue()*-1);
            toFlip = true;
            //handles negative exponents
    }
    while (exponent->getNumerator()>1)
    	{
        base->multiply(constantBase);
        Integer* one = new Integer(1);
        exponent->setNumerator(exponent->geteNumerator()->subtract(one));     //Error: cannot initialize a parameter of type 'Expression *' with an rvalue of type 'int'
    }
    if (toFlip) {
        Integer* one = new Integer(1);
        Rational* mouse = new Rational(one, base);
    	base = mouse;
    }

}

Expression* Exponential::add(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (ex->getBase()==this->base) {
		if (ex->getExponent()==this->exponent) {
			Integer* two = new Integer(2);
			this->multiply(two);
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
			Integer* zero = new Integer(0);
			this->multiply(zero);
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
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (this->base == ex->getBase()) {
		this->exponent->add(ex->getExponent());
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
	Rational* r = (Rational *) a;
	r->setNumerator(r->geteNumerator()->multiply(this));        //Error: expected expression
	return r;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Exponential::divide(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if (this->base == ex->getBase()) {
		this->exponent->subtract(ex->getExponent());
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
	Rational* r = (Rational *) a;
	r->setDenominator(r->geteDenominator()->multiply(this));      //Error: member reference type 'int' is not a pointer
	return r;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}

Rational* Exponential::getExponent() {
    return exponent;
}

Expression* Exponential::getBase() {
    return base;
}

Integer* Exponential::getExnu() {
	return exnu;
}

Integer* Exponential::getExde() {
	return exde;
}

void Exponential::setExnu(Integer* n) {
	exnu = n;
}

void Exponential::setExde(Integer* n) {
	exde = n;
}

void Exponential::setExponent(Rational* e) {
    exponent = e;
}

void Exponential::setBase(Expression* e) {
    base = e;
}

string Exponential::toString() {
    stringstream str;
    str << base << "^" << exponent;
    return str.str();
}


ostream& Exponential::print(std::ostream& output) const{
    output << this->base << this->exponent; //overload cout so that it makes sense
    return output;
}
