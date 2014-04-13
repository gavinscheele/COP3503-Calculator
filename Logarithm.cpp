//
// Logarithm.cpp
// Calculator
//
// Created by Gavin Scheele on 3/27/14.
// Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Logarithm.h"
#include <vector>
#include<math.h>

Logarithm::Logarithm(int base, int operand){
    this->type = "logarithm";
    this->base = base;
    this->operand = operand;
    this->eOperand = new Integer(operand);
    this->eBase = new Integer(base);
}

Logarithm::Logarithm(Expression* eBase, Expression* eOperand){
    this->type = "logarithm";
    this->eBase = eBase;
    this->eOperand = eOperand;
}

int Logarithm::getBase(){
	return base;
}
int Logarithm::getOperand(){
	return operand;
}
Expression* Logarithm::getEBase(){
	return eBase;
}
Expression* Logarithm::getEOperand(){
	return eOperand;
}

void Logarithm::setBase(Expression* x){
	this->eBase = x;
}
void Logarithm::setOperand(Expression* x){
	this->eOperand = x;
}

Logarithm::~Logarithm(){
    delete this;
}


Expression* Logarithm::simplify(){
        vector<int> primefactors = primeFactorization(operand);//Create a vector of all the prime factors of the operand
        int size1 = primefactors.size();//gets the size of this vector
        vector<Expression *> seperatedLogs(size1);//creates another vector of type expression to save all of the separated Logs has the same size of the number of prime factors


        for(int i = 0 ; i < size1; i++){
            seperatedLogs.at(i) = new Logarithm(this->eBase, primefactors.at(i));//assigns values to each seperatedlog with the same base and operands of the prime factorization
            }

       for(int j; j <size1; j++){
    	if (seperatedLogs.at(j)->type == "logarithm") {
            if (base == operand){
                Integer* inte= new Integer(1);
                seperatedLogs.at(j) = inte;
            }
            else if(base == (1/operand)){
                Integer* inten= new Integer(1);
                seperatedLogs.at(j) = inten;
			}
    	}
       }
       if(size1 >= 2){
        Expression* answer = seperatedLogs.at(0)->add(seperatedLogs.at(1));
       }
       else{
        Expression* answer = seperatedLogs.at(0);
       }


       for(int k = 1; k<size1; k++){
            answer = answer->add(seperatedLogs.at(k));

       }

}

vector<int> Logarithm::primeFactorization(int n) {
    int k = 0;
    vector<int> factors;
    while (n%2 == 0) {
        factors.push_back(2);
        k++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n%1 == 0) {
            factors.push_back(2);
            k++;
            n = n/i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}

Expression* Logarithm::add(Expression* a){
    Expression* c = this;
    if(c->base && a->base && c->operand && a->operand) {
    	if (c->getBase() == a->getBase() && c->getOperand() == a->getOperand()){
    		Expression* answer = new Expression(2->multiply(c));
    		return answer;
    	}

    }

    else if(c->eBase && a->eBase && c->operand && a->operand) {
    	if (c->getEBase() == a->getEBase() && c->getOperand() == a->getOperand()){
    		Expression* answer = new Expression(2->multiply(c));
    		return answer;
    	}

    }

    else if(c->base && a->base && c->eOperand && a->eOperand) {
    	if (c->getBase() == a->getBase() && c->getEOperand() == a->getEOperand()){
    		Expression* answer = new Expression(2->multiply(c));
    		return answer;
    	}

    }

    else if(c->eBase && a->eBase && c->eOperand && a->eOperand) {
    	if (c->getEBase() == a->getEBase() && c->getEOperand() == a->getEOperand()){
    		Expression* answer = new Expression(2->multiply(c));
    		return answer;
    	}

    }
    return c;
}
Expression* Logarithm::subtract(Expression* a){
    Expression* c = this;
    if(c->base && a->base && c->operand && a->operand) {
    	if (c->getBase() == a->getBase() && c->getOperand() == a->getOperand()){
    		Expression* answer = new Integer(0);
    		return answer;
    	}

    }

    else if(c->eBase && a->eBase && c->operand && a->operand) {
    	if (c->getEBase() == a->getEBase() && c->getOperand() == a->getOperand()){
    		Expression* answer =  new Integer(0);
    		return answer;
    	}

    }

    else if(c->base && a->base && c->eOperand && a->eOperand) {
    	if (c->getBase() == a->getBase() && c->getEOperand() == a->getEOperand()){
    		Expression* answer =  new Integer(0);
    		return answer;
    	}

    }

    else if(c->eBase && a->eBase && c->eOperand && a->eOperand) {
    	if (c->getEBase() == a->getEBase() && c->getEOperand() == a->getEOperand()){
    		Expression* answer =  new Integer(0);
    		return answer;
    	}

    }
    return c;
}
Expression* Logarithm::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Logarithm::print(std::ostream& output) const{
    output << "Log_" << this->base << ":" << this->operand;
    return output;
}
string Logarithm::toString(){
    stringstream ss;
    ss << "Log_" << this->base << "(" << this->operand;
};


// might need later had in simplify metthod not sure
/*int i = 1;
		int x = operand;
		int y = base;
	 	if(x % y == 0 &&) {
			while (x>y) {
				x /=y ;
				i++;}
			Expression* simplified = new Integer(i);
			return simplified; }
*/
