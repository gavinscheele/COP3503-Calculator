//
//  Pi.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Pi.h"
Pi::Pi(){
    this->type = "pi";
    this->coefficient = new Integer(1);
}
Pi::~Pi(){
    delete this;
}
Integer* Pi:: getCoefficient()
{
	return coefficient;
}
void Pi:: setCoefficient(Integer* x)
{
	this->coefficient = x;
}

Expression* Pi::add(Expression* a){
    Pi* c = this;

	if(a->type == "pi"){
        Pi *b = (Pi *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = thisCoef->add(aCoef);
		c->setCoefficient(sum);
		return c;
	}
}
Expression* Pi::subtract(Expression* a){
    Pi* c = this;

	if(a->type == "pi"){
        Pi *b = (Pi *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = thisCoef->subtract(aCoef);
		c->setCoefficient(sum);
		return c;
	}

}
Expression* Pi::multiply(Expression* a){
    Pi* c = this;

	 if(a->type == "pi"){
        Pi *b = (Pi *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* product = thisCoef->multiply(aCoef);
		Exponential* e = new Exponential(pi,2);
		Expression* d = e->multiply(product);
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;
        if(b->getBase() == "pi"){
            Expression* exponent = b->getExponent();
            Exponential* product = new Exponential("pi",exponent + 1);
            Integer* Coef = c->getCoefficient();
            Expression* d = Coef->multiply(product);
            return d;
            }
        }

}
Expression* Pi::divide(Expression* a){
     Pi* c = this;

	 if(a->type == "pi"){
        Pi *b = (Pi *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* product = thisCoef->divide(aCoef);
		Exponential* e = new Exponential(e,2);
		Expression* d = e->multiply(product);
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;
        if(b->getBase() == "pi"){
            Expression* exponent = b->getExponent();
            Exponential* product = new Exponential("pi",1 - exponent);
            Integer* Coef = c->getCoefficient();
            Expression* d = Coef->multiply(product);
            return d;
        }

	}


}

string Pi:: toString(){
    stringstream s;
	s<<this->coefficient<<"pi";
	return s.str();
}

}
ostream& Pi::print(std::ostream& output) const{
    output << this->coefficient << "Pi";
    return output;
}
