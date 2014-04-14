//
// Logarithm.cpp
// Calculator
//
// Created by Gavin Scheele on 3/27/14.
// Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Logarithm.h"
using namespace std;

Logarithm::Logarithm(int base, int operand){
    if (operand == 0){
    throw runtime_error("Logarithms of 0 are undefined.");
    }
    if (operand < 0) {
    throw runtime_error("Logarithms of negative numbers are undefined.");
    }
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

       for(int j; j <size1; j++)
    	if (seperatedLogs.at(j)->type == "logarithm") {//checks to see if the value at seperated log is a log type
            if(eBase->type == eOperand->type){ //makes sure the ebase and eoperand are of the same type
                if (eBase == eOperand){// checks to see if the ebase and the eOperand are the same
                    Integer* inte= new Integer(1);//returns one if they are the same
                    seperatedLogs.at(j) = inte;//assigns 1 to the value of seperated log at j
                }
                }
    	}


       Expression * answer;//creates a new variable called answer
       if(size1 >= 2){// if the size is two or higher
        answer = seperatedLogs.at(0)->add(seperatedLogs.at(1));// add the first two together
       }
       else{//if the size is just 1
        answer = seperatedLogs.at(0);//the answer is the first one
       }


       for(int k = 1; k<size1; k++){
            answer = answer->add(seperatedLogs.at(k));//keeps adding elements of seperated log to answer

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
    return this;
}
Expression* Logarithm::subtract(Expression* a){
    Logarithm* c = this;
    Logarithm* b = (Logarithm *) a;
    if(c->eBase->type == b->eBase->type && c->eOperand->type == b->eOperand->type) {
    	if (c->getEBase() == b->getEBase() && c->getEOperand() == b->getEOperand()){
    		Expression* answer = new Integer(0);
    		return answer;
    	}
    }
    return c;
}

Expression* Logarithm::multiply(Expression* a){
    Logarithm* c = this;
    Logarithm* b = (Logarithm *) a;
    if(c->eBase->type == b->eBase->type && c->eOperand->type == b->eOperand->type) {
    	if (c->getEBase() == b->getEBase() && c->getEOperand() == b->getEOperand()){
    		Exponential* answer = new Exponential(this, new Rational(2,1));
    		return answer;
    	}
    }
   return c;
}
Expression* Logarithm::divide(Expression* a){//this set up is "this" divided by a so if this = log11 and a = log3 it would be log11/log3
    Logarithm* c = this;
    Logarithm* b = (Logarithm *) a;
    if(c->eBase->type == b->eBase->type && c->getEBase() == b->getEBase()) {
        Expression* numeratorOperand = c->getEOperand();
        Expression* denominatorOperand = b->getEOperand();
        Logarithm* answer = new Logarithm(denominatorOperand, numeratorOperand);
        return answer;
    }

    return c;
}
ostream& Logarithm::print(std::ostream& output) const{
    output << "Log_" << this->eBase << ":" << this->eOperand;
    return output;
}
string Logarithm::toString(){
    stringstream ss;
    ss << "Log_" << this->eBase << "(" << this->eOperand;
    return ss.str();
};
