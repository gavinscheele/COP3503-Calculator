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
		Integer* sum = (Integer *)thisCoef->add(aCoef);
		c->setCoefficient(sum);
	}
    return c;

}
Expression* Pi::subtract(Expression* a){

  Pi* c = this;

	if(a->type == "pi"){
        Pi *b = (Pi *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = (Integer *)thisCoef->subtract(aCoef);
		c->setCoefficient(sum);
	}
    return c;


}
Expression* Pi::multiply(Expression* a){
    Pi* c = this;

	 if(a->type == "pi"){
        Pi *b = (Pi *)a;//Casts a
		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's being multiplied
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this
		Integer* product = (Integer *)thisCoef->multiply(aCoef);//Multiplies two coefficients together
		Pi* pi1 = new Pi();//creates new Pi
		Exponential* exponential = new Exponential((Expression *)pi1,(Rational *)2);//Creates new Exponential with base pi and exponent 2
		Expression* d = exponential->multiply(product);//multiplies the new pi^2 by the multiplied product
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "pi"){ // Checks to see if the base is pi
            Rational* exponent = b->getExponent();//gets exponent of b
            Pi* pi2 = new Pi();//creates new Pi
            Rational* one = new Rational(1,1);
            Exponential* product = new Exponential((Expression*)pi2,(Rational *)(exponent->add(one)));
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type pi
            Expression* d = Coef->multiply(product);//multiplies the coefficient of e with the new Exponential type
            return d;
            }
        }

	}


Expression* Pi::divide(Expression* a){
	  Pi* c = this;

	 if(a->type == "pi"){
        Pi *b = (Pi *)a;//Casts a
		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's dividing (x/a)...a
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this(x/a)..x
		Integer* product = (Integer *)thisCoef->divide(aCoef);//Divides this by a
		return product;//pi divided by pi is 1, so we just return the product
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "pi"){ // Checks to see if the base is pi
            Rational* exponent = b->getExponent();//gets exponent of b
            Pi* pi2 = new Pi();//creates new Pi
            Rational* one = new Rational(1,1);
            Exponential* product = new Exponential((Expression*)pi2,(Rational *)(one->subtract(exponent)));// creates new Exponential with base e and exponent 1 - previous exponent
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type pi
            Expression* d = Coef->multiply(product);//multiplies the coefficient of pi with the new Exponential type
            return d;
            }
        }

	}


string Pi:: toString(){
    stringstream s;
	s<<this->coefficient<<"pi";
	return s.str();
}

ostream& Pi::print(std::ostream& output) const{
    output << this->coefficient << "Pi";
    return output;
}
