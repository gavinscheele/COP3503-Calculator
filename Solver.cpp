//
//  Solver.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"


Solver::Solver(std::string a){
    this->localExpression = a;
    expressions = *new vector<string>();
    tokenStack = *new stack<string>();
    output = "";
}
Solver::~Solver(){
    
}
std::string Solver::solve(bool floatingPoint){
    string temp = "";
    int count = 0;
    
    for(int i = 0; i < localExpression.size(); i ++){       //creates an array of expressions and operations
        if(localExpression.at(i) == ' '){
            temp = "";
            for (int j = count; j < i; j++) {
                temp.push_back(localExpression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;

        }else if(i == localExpression.size()-1){
            temp = "";
            for (int j = count; j <= i; j++) {
                temp.push_back(localExpression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
        }
    }
    
    shuntingYard();
    
    expressions.clear();
    count = 0;
    
    
    for(int i = 0; i < output.size(); i ++){       //creates an array of expressions and operations
        if(output.at(i) == ' '){
            temp = "";
            for (int j = count; j < i; j++) {
                temp.push_back(output.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
            
        }else if(i == output.size()-1){
            temp = "";
            for (int j = count; j <= i; j++) {
                temp.push_back(output.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
        }
    }
    if (floatingPoint) {
        return evaluateFloatString();
    }else return evaluateString();

}
void Solver::shuntingYard(){
    for(int i = 0; i < expressions.size(); i++){
        string token = expressions.at(i);
        
        if(!isAnOperator(token) && (token != "(" && token != ")")){
            if(i == 0) output += expressions.at(i);
            else output += " " + expressions.at(i);
        }
        
        if(isAnOperator(token)){
            while(!tokenStack.empty() && isAnOperator(tokenStack.top()) ){
                if((isLeftAssociative(token) && getOperatorPrecedence(token) <= getOperatorPrecedence(tokenStack.top())) ||
                   (!isLeftAssociative(token) && getOperatorPrecedence(token) < getOperatorPrecedence(tokenStack.top()))){
                    output += " " + tokenStack.top();
                    tokenStack.pop();
                }
                break;

            }
            tokenStack.push(token);
        }
        
        if(token == "("){
            tokenStack.push(token);
        }
        
        if(token == ")"){
            while (!tokenStack.empty() && tokenStack.top() != "(") {
                output += " " + tokenStack.top();
                tokenStack.pop();
            }
            tokenStack.pop();
        }
    }
    while (!tokenStack.empty()) {
        output += " " + tokenStack.top();
        tokenStack.pop();
    }
    if(output.at(0) == ' '){
        output.erase(0,1);
    }
}
bool Solver::isAnOperator(string tkn){
    if(tkn == "+" || tkn == "-" || tkn == "/" || tkn == "*" || tkn == "^") return true;
    else return false;
}

bool Solver::isLeftAssociative(string tkn){
    if(tkn == "+" || tkn == "-" || tkn == "/" || tkn == "*") return true;
    else return false;

}
int Solver::getOperatorPrecedence(string tkn){
    if(tkn == "^") return 4;
    else if(tkn == "*" || tkn == "/") return 3;
    else return 2;
}
string Solver::evaluateFloatString(){
    string out = *new string("");
    string result = *new string("");
    stack<string> stk = *new stack<string>();
    
    if (expressions.size() == 1) {
        out = this->bindToExpressionType(expressions.at(0))->toString();
        return out;
    }
    for(int i = 0; i < expressions.size(); i++){
        string token = expressions.at(i);
        
        if(!isAnOperator(token)){
            stk.push(token);
        }
        else{
            Expression* e2;
            e2 = bindToExpressionType(stk.top());
            e2->exp =  stk.top();
            stk.pop();
            
            Expression *e1;
            e1 = bindToExpressionType(stk.top());
            e1->exp = stk.top();
            result = e1->exp;
            stk.pop();
            
            //check function call and call appropriate method
            if(token == "+"){
                if(e1->canAdd(e2)){
                    Expression *result = e1->add(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "+" + e2->exp);
                    out += e1->exp + " + " + e2->exp;
                }
            }else if(token == "-"){
                if(e1->canSubtract(e2)){
                    Expression *result =  e1->subtract(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "-" + e2->exp);
                    out += e1->exp + " - " + e2->exp;
                }
            }else if(token == "*"){
                if(e1->canMultiply(e2)){
                    Expression *result = e1->multiply(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "*" + e2->exp);
                    out += e1->exp + " * " + e2->exp;
                }
                
            }else if(token == "/"){
                if (e1->type == "integer" && e2->type == "integer") {
                    Integer *a = (Integer *)e1;
                    Integer *b = (Integer *)e2;
                    if(b->getValue() == 0) throw runtime_error("Error: Cannot Divide By Zero");
                    if (a->getValue() % b->getValue() != 0) {
                        e1 = new Rational(e1,e2);
                        stk.push(e1->toString());
                        out += e1->toString();
                    }else if(e1->canDivide(e2)){
                        Expression *result = e1->divide(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }
                else if(e1->canDivide(e2)){
                    Expression *result = e1->divide(e2);
                    if (result->type == "rational") {
                        Rational * a = (Rational *)result;
                        if (a->getNumerator() == 1 && a->getDenominator() == 1) {
                            stk.push("1");
                            out = "1";
                        }else{
                            stk.push(result->toString());
                            out = result->toString();
                        }
                    }else{
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }
            }else if(token == "^"){
                if (e2->type == "integer") {
                    Rational *b = new Rational(e2, new Integer(1));
                    e2 = b;
                }
                Exponential *a = new Exponential(e1,(Rational *)e2);
                output += a->toString();
                Rational *t = (Rational *)e2;
                if (t->getNumerator() == 1 && t->getDenominator() == 1) {
                    stk.push(e1->toString());
                    out += e1->toString();
                }else{
                    stk.push(e1->toString() + "^" + e2->toString());
                    out += e1->toString() + "^" + e2->toString();
                }
                
                
            }else{
                cout << "Error: Invalid Operator" << endl;
            }
            
        }
        
    }
    return out;
}
string Solver::evaluateString(){
    string out = *new string("");
    string result = *new string("");
    stack<string> stk = *new stack<string>();
    
    if (expressions.size() == 1) {
        out = this->bindToExpressionType(expressions.at(0))->toString();
        return out;
    }
    for(int i = 0; i < expressions.size(); i++){
        string token = expressions.at(i);
        
        if(!isAnOperator(token)){
            stk.push(token);
        }
        else{
            Expression* e2;
            e2 = bindToExpressionType(stk.top());
            e2->exp =  stk.top();
            stk.pop();
            
            Expression *e1;
            e1 = bindToExpressionType(stk.top());
            e1->exp = stk.top();
            result = e1->exp;
            stk.pop();
            
            //check function call and call appropriate method
            if(token == "+"){
                if(e1->canAdd(e2)){
                    Expression *result = e1->add(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "+" + e2->exp);
                    out += e1->exp + " + " + e2->exp;
                }
            }else if(token == "-"){
                if(e1->canSubtract(e2)){
                   Expression *result =  e1->subtract(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "-" + e2->exp);
                    out += e1->exp + " - " + e2->exp;
                }
            }else if(token == "*"){
                if(e1->canMultiply(e2)){
                    Expression *result = e1->multiply(e2);
                    stk.push(result->toString());
                    out = result->toString();
                }else{
                    stk.push(e1->exp + "*" + e2->exp);
                    out += e1->exp + " * " + e2->exp;
                }
                
            }else if(token == "/"){
                if (e1->type == "integer" && e2->type == "integer") {
                    Integer *a = (Integer *)e1;
                    Integer *b = (Integer *)e2;
                    if(b->getValue() == 0) throw runtime_error("Error: Cannot Divide By Zero");
                    if (a->getValue() % b->getValue() != 0) {
                        e1 = new Rational(e1,e2);
                        stk.push(e1->toString());
                        out += e1->toString();
                    }else if(e1->canDivide(e2)){
                        Expression *result = e1->divide(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }
                else if(e1->canDivide(e2)){
                    Expression *result = e1->divide(e2);
                    if (result->type == "rational") {
                        Rational * a = (Rational *)result;
                        if (a->getNumerator() == 1 && a->getDenominator() == 1) {
                            stk.push("1");
                            out = "1";
                        }else{
                            stk.push(result->toString());
                            out = result->toString();
                        }
                    }else{
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }
            }else if(token == "^"){
                if (e2->type == "integer") {
                    Rational *b = new Rational(e2, new Integer(1));
                    e2 = b;
                }
                Exponential *a = new Exponential(e1,(Rational *)e2);
                output += a->toString();
                Rational *t = (Rational *)e2;
                if (t->getNumerator() == 1 && t->getDenominator() == 1) {
                    stk.push(e1->toString());
                    out += e1->toString();
                }else{
                    stk.push(e1->toString() + "^" + e2->toString());
                    out += e1->toString() + "^" + e2->toString();
                }


            }else{
                cout << "Error: Invalid Operator" << endl;
            }
            
        }

    }
    return out;
}
Expression* Solver::bindToExpressionType(string e){
    Expression *a = new Integer(0);     //so the compiler doesnt complain. Will be set to appropriate type later

    for(int i = 0; i < e.length(); i++){
        if (e[i] == '/') {
            string before;
            string after;
            for(int j = 0; j < i; j++){
                before.push_back(e[j]);
            }
            for(int k = i+1; k < e.length(); k++){
                after.push_back(e[k]);
            }
            a = new Rational(atoi(before.c_str()), atoi(after.c_str()));
            break;
        }else if(e[i] == 'p' && e[i+1] == 'i'){
            a = new Pi();
            break;
        }else if(e[i] == 'e'){
            a = new Euler();
            break;
        }else if(e[i] == 'l' && e[i+1] == 'o' && e[i+2] == 'g'){
            string base;
            string operand;
            int  j = i + 4;
            while (e[j] != ':') {
                base.push_back(e[j]);
                j++;
            }
            for (int k = j+1; k < e.length(); k++) {
                operand.push_back(e[k]);
            }
            Expression *b = this->bindToExpressionType(base);
            Expression *o = this->bindToExpressionType(operand);
            if (b->type == "integer" && o->type == "integer") {
                Integer *ba = (Integer *)b;
                Integer *op = (Integer *)o;
                Logarithm *b = new Logarithm(ba->getValue(), op->getValue());
                Logarithm *c = (Logarithm *)b->simplify();
                if (c->getBase() == b->getBase() && c->getOperand() == b->getOperand()) {
                }
            }else{
                a = new Logarithm(b,a);
            }
            break;
        }
        else if(!isdigit(e[i]) && e[i] != '-'){
            cout << e[i] << endl;
            break;
        }
        else if(i == e.length()-1){
            a = new Integer(atoi(e.c_str()));
        }
    }
    return a;
}
bool Solver::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}











                  
                  
                  
                  
                  
                  
