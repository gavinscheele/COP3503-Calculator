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
		Integer* zero = new Integer(0);
		if((c->coefficient->getValue()) == 0)
        {
            return zero;
        }
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
		pi1->setCoefficient(product);
		Rational* two = new Rational(2,1);
		Exponential* exponential = new Exponential((Expression*)pi1,two);//Creates new Exponential with base pi and exponent 2
		return exponential;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "pi"){ // Checks to see if the base is pi
            Rational* exponent = b->getExponent();//gets exponent of b
            Pi* pi2 = new Pi();//creates new Pi
            Rational* one = new Rational(1,1);
            Rational* exponSum =(Rational *)exponent->add(one);
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type pi
            pi2->setCoefficient(Coef);
            Exponential* product = new Exponential((Expression*)pi2,exponSum);
            return product;
            }
        }
        //need to return something if its not these two cases. Added return c.
        return c;
	}


Expression* Pi::divide(Expression* a){
	  Pi* c = this;

	 if(a->type == "pi"){//This doesn't work because of the integer divide method.
        Pi *b = (Pi *)a;//Casts a
		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's dividing (x/a)...a
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this(x/a)..x
		Expression* product = thisCoef->divide(aCoef);//Divides this by a
		return product;//pi divided by pi is 1, so we just return the product
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "pi"){ // Checks to see if the base is pi
            Rational* exponent = b->getExponent();//gets exponent of b
            Pi* pi2 = new Pi();//creates new Pi
            Rational* one = new Rational(1,1);
            Rational* exponSum =(Rational*)one->subtract(exponent);
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type pi
            pi2->setCoefficient(Coef);
            Exponential* product = new Exponential((Expression*)pi2,exponSum);// creates new Exponential with base pi and exponent 1 - previous exponent
            return product;
            }
        }
    //need to return something if neither of these cases are met. added return c.
    return c;

	}


string Pi:: toString(){
    stringstream s;
    if(this->coefficient->getValue() == 1){
        s << "pi";
    }else
        s<<*this->coefficient <<" " <<"*"<<" "<<"pi";
    
	return s.str();
}

ostream& Pi::print(std::ostream& output) const{
    if(this->coefficient->getValue() == 1){
        output << "pi";
    }else
        output<<*this->coefficient <<" " <<"*"<<" "<<"pi";
    
    return output;
}


