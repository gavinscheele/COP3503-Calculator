//
// Logarithm.cpp
// Calculator
//
// Created by Gavin Scheele on 3/27/14.
// Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Logarithm.h"
using namespace std;
#include <string>

//constructor for int base with an int operand
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

//constructor for expression base and or expression operand
Logarithm::Logarithm(Expression* eBase, Expression* eOperand){
    this->type = "logarithm";
    this->eBase = eBase;
    this->eOperand = eOperand;

}
//get-set methods below
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

Expression* Logarithm::simplifyOperand(){
    Expression* e = this->eOperand;
    e->exp = e->toString();
    string operand1 = e->exp;
    cout<<operand1;
        char asterick = '*';
        char slash = '/';
        vector<int> position;
        vector<char> symbols;
        int length = operand1.length();
        for(int i = 0; i < length; i++)
        {
            if(operand1.at(i)== (asterick) || operand1.at(i)== slash){
                position.push_back(i);
                position.push_back(operand1.at(i));
                cout<<i<<endl;
            }
        }
        string number = "";
        vector<Expression* > logs;
        for(int j =0; j<=position.size();j++){
                int positionofop = position.at(j);
                string number = operand1.substr(j,positionofop-2);
                Solver* s = new Solver();
                Expression* e = s->bindToExpressionType(number);
                Logarithm* simpleLog = (Logarithm*)e;
                simpleLog->simplify();
                logs.push_back(e);

        }

        Expression* endlog = new Integer(0);
         endlog->type = "multiple";
          stringstream endlogexp;
          for(int k = 0; k<logs.size(); k++){
            endlogexp<<*logs.at(k);
            if(k+1 < logs.size()&& symbols.at(k == asterick)){
                endlogexp<< " " << "+" << " ";
            }
            if(k+1 < logs.size()&& symbols.at(k == slash)){
                endlogexp<< " " << "-" << " ";
            }
            }
        endlog->exp = endlogexp.str();
        return endlog;



}
Expression* Logarithm::simplify(){


        if(eOperand->type == "euler")
        {

            if(eBase->type == "euler"){
                Integer* answer = new Integer(1);
                return answer;
            }
            else{
                Logarithm* answer = new Logarithm(eBase, eOperand);
                return answer;
            }

        }

        if(eOperand->type == "pi")
        {
             if(eBase->type == "pi"){
                Integer* answer = new Integer(1);
                return answer;
            }
            else{
                Logarithm* answer = new Logarithm(eBase, eOperand);
                return answer;
            }

        }

       if(eOperand->type == "integer"){

        vector<int> primefactors = primeFactorization(operand);//Create a vector of all the prime factors of the operand
        size_t size1 = primefactors.size();//gets the size of this vector
        vector<Expression *> seperatedLogs(size1);//creates another vector of type expression to save all of the separated Logs has the same size of the number of prime factors


        for(int i = 0 ; i < size1; i++){
            seperatedLogs.at(i) = new Logarithm(this->eBase, new Integer(primefactors.at(i)));//assigns values to each seperatedlog with the same base and operands of the prime factorization
            }


       for(int j= 0; j <size1; j++){

    	if (seperatedLogs.at(j)->type == "logarithm") {//checks to see if the value at seperated log is a log type
            Logarithm* a = (Logarithm *)seperatedLogs.at(j);
            Logarithm* log = new Logarithm(a->getEBase(),a->getEOperand());
            if(log->eBase->type == log->eOperand->type && log->eBase->type == "integer"){ //makes sure the ebase and eoperand are of the same type
                Integer* b = (Integer *)(log->eBase);
                Integer* c = (Integer *)(log->eOperand);
                if (b->getValue() == c->getValue()){// checks to see if the ebase and the eOperand are the same
                    Integer* inte= new Integer(1);//returns one if they are the same
                    seperatedLogs.at(j) = inte;//assigns 1 to the value of seperated log at j


                }
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


       for(int k = 2; k<size1; k++){
            answer = answer->add(seperatedLogs.at(k));//keeps adding elements of seperated log to answer

       }
       Integer* size2 = new Integer((int)size1);
       Integer* answerint = (Integer *)answer;
       if(answerint->getValue()==size2->getValue())
       {
           return answer;
       }
       else if(size1 == 1){
        return this;
       }
       else
       {
          Expression* e = new Integer(answerint->getValue());
          e->type = "multiple";
          stringstream s;
          for(int l = 0; l<size1; l++){
            s<<*seperatedLogs.at(l);
            if(l+1 < size1){
                s<< " " << "+" << " ";
            }
            }
        e->exp = s.str();
        cout<<e->exp;
        return e;
       }
       }

       throw runtime_error("invalid entry");
       return this;
}

//creates vector of prime factors of n to be used in the simplify method
vector<int> Logarithm::primeFactorization(int n) {
    int k = 0;
    vector<int> factors;
    while (n%2 == 0) {
        factors.push_back(2);
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n%i == 0) {
            factors.push_back(i);
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
    output << "Log_" << *eBase << ":" << *eOperand<< endl;

    return output;
}
string Logarithm::toString(){
    stringstream ss;
    ss << "Log_" << *this->eBase << ":" << *this->eOperand;

    return ss.str();
};
