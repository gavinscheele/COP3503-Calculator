//
//  Euler.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//
//

#include "Euler.h"
Euler::Euler(){
    this->type = "euler";
    this->coefficient = new Integer(1);
}
Euler::~Euler(){
    delete this;
}
Integer* Euler:: getCoefficient()
{
	return coefficient;
}
void Euler:: setCoefficient(Integer* x)
{
	this->coefficient = x;
}
Expression* Euler::add(Expression* a){
   Euler* c = this;

	if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = thisCoef->add(aCoef);
		c->setCoefficient(sum);
		return c;
	}

}
Expression* Euler::subtract(Expression* a){

  Euler* c = this;

	if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = thisCoef->subtract(aCoef);
		c->setCoefficient(sum);
		return c;
	}

}
Expression* Euler::multiply(Expression* a){
    Euler* c = this;

	 if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* product = thisCoef->multiply(aCoef);
		Exponential* e = new Exponential(e,2);
		Expression* d = e->multiply(product);
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;
        if(b->getBase() == "e"){
            Expression* exponent = b->getExponent();
            Exponential* product = new Exponential("e",exponent + 1);
            Integer* Coef = c->getCoefficient();
            Expression* d = Coef->multiply(product);
            return d;
            }
        }

	}


Expression* Euler::divide(Expression* a){


	  Euler* c = this;

	 if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* product = thisCoef->divide(aCoef);
		Exponential* e = new Exponential(e,2);
		Expression* d = e->multiply(product);
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;
        if(b->getBase() == "e"){
            Expression* exponent = b->getExponent();
            Exponential* product = new Exponential("e",1 - exponent);
            Integer* Coef = c->getCoefficient();
            Expression* d = Coef->multiply(product);
            return d;
        }

	}

	}


string Euler:: toString()
{
	stringstream s;
	s<<this->coefficient<<"e";
	return s.str();
}
ostream& Euler::print(std::ostream& output) const{
    output << this->coefficient << "e";  //overload cout of this class so that it makes sense
    return output;
}
