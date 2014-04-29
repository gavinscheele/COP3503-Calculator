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
	this->exponent->getNumerator()
	if (this->exNu == 0) {
		return true;
	}
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
	Integer* one = new Integer(1);
	if (this->exNu == 0) {
		return one;
	}
        Rational* oneRat = new Rational(1, 1);
	if (this->base->type == "rational") {
		Rational* ratBase = (Rational *) this->base;
		Exponential* numAsExponential = new Exponential ((ratBase->geteNumerator()), (this->exponent));  //no matching constructor for exponential
		Exponential* denAsExponential = new Exponential ((ratBase->geteDenominator()), (this->exponent));    //same error
		Rational* newRatBase = new Rational(numAsExponential, denAsExponential);
		this->base = newRatBase;
		this->exponent = oneRat;
	}
	else {

    if (this->exponent->getNumerator()==0) {
        
       this->exponent=oneRat;
       this->base=one;

    }
    bool toFlip = false;
    if (exnu->getValue()<0) {
	    exnu->setValue(exnu->getValue()*-1);
            toFlip = true;
            //handles negative exponents
    }
    Expression* constantBase = 0;
    if (base->type == "integer") {              //fixed the problem for integers but nothing else
        Integer *a = (Integer *)base;
        constantBase = new Integer(a->getValue());
    }


    while (exponent->getNumerator()>1)
    	{
        base->multiply(constantBase);
        exponent->setNumerator(exponent->geteNumerator()->subtract(one));
    }
    if (toFlip) {
        Integer* one = new Integer(1);
        Rational* mouse = new Rational(one, base);
    	base = mouse;
    }
    
	}

}

Expression* Exponential::add(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	if ((ex->getBase()->type == this->base->type) && ((this->base->type == "euler") || (this->base->type == "pi"))) {
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
	if ((ex->getBase()->type == this->base->type) && ((this->base->type == "euler") || (this->base->type == "pi"))) {
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
    		if (this->base->type == "euler") {
    			Rational* oneRat = new Rational(1, 1);
			this->exponent->add(oneRat);
    		
    	}

    }else if(a->type == "exponential"){
		Exponential* ex = (Exponential *) a;
	//if (this->base == ex->getBase()) {
	//	this->exponent->add(ex->getExponent());
	//}
	if (ex->base->type == this->base->type) {
		if ((ex->base->type == "euler") || (ex->base->type == "pi")) {
			this->exponent->add(ex->exponent);
		}
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){
    	if (this->base->type == "pi") {
    			Rational* oneRat = new Rational(1, 1);
			this->exponent->add(oneRat);
    	}

    }else if(a->type == "rational"){
	Rational* r = (Rational *) a;
	Expression* numToSet = r->geteNumerator();
	numToSet->multiply(this);
	r->setNumerator(numToSet);
	return r;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Exponential::divide(Expression* a){
	if(a->type == "euler"){
		if (this->base->type == "euler") {
    				Rational* oneRat = new Rational(1, 1);
				this->exponent->subtract(oneRat);
    		}

    }else if(a->type == "exponential"){
	Exponential* ex = (Exponential *) a;
	//if (this->base == ex->getBase()) {
	//	this->exponent->subtract(ex->getExponent());
	//}
	if (ex->base->type == this->base->type) {
		if ((ex->base->type == "euler") || (ex->base->type == "pi")) {
			this->exponent->subtract(ex->exponent);
		}
	}

    }else if(a->type == "integer"){

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){
    	if (this->base->type == "pi") {
    				Rational* oneRat = new Rational(1, 1);
				this->exponent->subtract(oneRat);
    		}

    }else if(a->type == "rational"){
	Rational* r = (Rational *) a;
	Expression* denToSet = r->geteDenominator();
	denToSet->multiply(this);
	r->setDenominator(denToSet);
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
    if(exponent->getNumerator() == 1 && exponent->getDenominator() == 1){
        str << *base;
    }
    else if(exponent->getDenominator() == 1){
        str << *base << "^" << *exponent->geteNumerator();
    }else{
        str << *base << "^" << *exponent;
    }
    return str.str();
}


ostream& Exponential::print(std::ostream& output) const{
    Exponential *a = (Exponential *)this;
    output << a->toString();
    return output;
}



bool Exponential::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)
    
    if (this->type == b->type && this->type != "logarithm") {
        if (this->type == "nthRoot") {
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool Exponential::canSubtract(Expression* b){
    if (this->type == b->type) {
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool Exponential::canMultiply(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if (this->base->type == b->type) {
    	return true;
    }
    else if(this->type == "integer" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
    
}
bool Exponential::canDivide(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if (this->base->type == b->type) {
    	return true;
    }
    else if(this->type == "integer"){
        if( b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
