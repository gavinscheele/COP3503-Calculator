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
    Integer *exde = (Integer *)exponent->getDenominator();  //warning: Cast to 'Integer *' from smaller integer type 'int'
    if (exde->getValue() != 1) {
        base = nthRoot(exde, base);             //error: no matching contructor for initialization of 'nthRoot'
        exponent = exponent->getNumerator();        //error: assigning to 'Rational *' from incompatible type 'int'
    }
    Integer *exnu = (Integer *)exponent->getNumerator();    //warning: Cast to 'Integer *' from smaller integer type 'int'
    if (canExponentiate()) {
    this = exponentiate();      //you can't assign 'this'. Just set your private variables in exponentiate
    }
}
Exponential::~Exponential(){

}

bool Exponential::canExponentiate() {
    if(base->type == "euler"){
        return false;

    }else if(base->type == "exponential"){
	Exponential* ex = (Exponential *) base;
	this->exponent *= ex->getExponent(); //did you mean "this->exponent->multiply(ex->getExponent);" ?
	Integer* numSum = new Integer (1);
	ex->getExponent()->setNumerator(numSum);    //syntax change
        return false;			// false is returned because the base itself would have already been exponentiated if it were possible

    }else if(base->type == "integer"){
        return true;
        

    }else if(base->type == "logarithm"){
        return false;

    }else if(base->type == "nthRoot"){
	nthRoot* nr = (nthRoot *) base;
	Rational* r = new Rational(this->exponent, nr->getRoot());      //error: no matching constructor for initialization of 'Rational'
	this->exponent = r;
	nr->setRoot(1);     //changed syntax

    }else if(base->type == "pi"){
        return false;

    }else if(base->type == "rational"){
        Rational* r = (Rational *) base;
        if (r->getNumerator()->type == "integer" && r->getDenominator()->type == "integer") {   //error: member reference type 'int' is not a pointer
          Exponential* nu = new Exponential(r->getNumerator(), this->exponent);     //error: no matching contructor for initialization of Exponential
          r->setNumerator(nu);
          Exponential* de = new Exponential(r->getDenominator(), this->exponent);   //error: no matching contructor for initialization of Exponential
          r->setDenominator(de);
        }

    }else{
        cout << "type not recognized" << endl;
    }
    return false;
}

Expression* Exponential::exponentiate(){
    Expression* toReturn = base;
    Expression* constantBase = base;
    if (this->exponent->getNumerator()==0) {        //changed . to ->
        Integer* ret = new Integer(1);
        return ret;
    }
    bool toFlip = false;
    if (exnu<0) {       //exnu is not a declared variable
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
