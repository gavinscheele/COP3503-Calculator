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
std::string Solver::solve(){
    string temp = "";
    int count = 0;
    
    for(int i = 0; i < localExpression.size(); i ++){       //creates an array of expressions and operations
        if(localExpression.at(i) == ' '){
            temp = "";
            if(count == 0){
                temp.push_back(localExpression.at(0));
                expressions.push_back(temp);
            }
            for(int j = count+1; j < i; j++){
                if(j == 1){
                    temp.push_back(localExpression.at(0));
                }
                temp.push_back(localExpression.at(j));
            }
            if(i != 0) expressions.push_back(temp);
            count = i;

        }else if(i == localExpression.size()-1){
            temp = "";
            temp.push_back(localExpression.at(i));
            expressions.push_back(temp);
        }
    }
    
    shuntingYard();
    
    expressions.clear();
    count = 0;
    for(int i = 0; i < output.size(); i ++){       //creates an array of expressions and operations in RPN form
        if(output.at(i) == ' '){
            temp = "";
            for(int j = count+1; j < i; j++){
                if(j == 1){
                    temp.push_back(localExpression.at(0));
                }
                temp.push_back(output.at(j));
            }
            if(i != 0) expressions.push_back(temp);

            count = i;
            
        }else if(i == output.size()-1){
            temp = "";
            temp.push_back(output.at(i));
            expressions.push_back(temp);
        }
    }
    
   // cout << output << endl;
    
    return "Result:" + output; //+ evaluateString();
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
string Solver::evaluateString(){
    string out = *new string("");
    string result = *new string("");
    stack<string> stk = *new stack<string>();
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
                    e1->add(e2);
                    stk.push(e1->exp);
                }else{
                    stk.push(e1->exp + "+" + e2->exp);
                    out += e1->exp + " + " + e2->exp;
                }
            }else if(token == "-"){
                if(e1->canSubtract(e2)){
                    e1->subtract(e2);
                }else{
                    stk.push(e1->exp + "-" + e2->exp);
                    out += e1->exp + " - " + e2->exp;
                }
            }else if(token == "*"){
                if(e1->canMultiply(e2)){
                    e1->multiply(e2);
                }else{
                    stk.push(e1->exp + "*" + e2->exp);
                    out += e1->exp + " * " + e2->exp;
                }
                
            }else if(token == "/"){
                if(e1->canDivide(e2)){
                    e1->divide(e2);
                }else{
                    e1 = new Rational(e1,e2);
                    stk.push(e1->exp + "/" + e2->exp);
                    out += e1->exp + " / " + e2->exp;
                }
            }else if(token == "^"){
             //   Expression *a = new Exponential(e1,e2);
               // output += a->exp;
                stk.push(e1->exp + "^" + e2->exp);
                out += e1->exp + "^" + e2->exp;

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
        if(!isdigit(e[i])){
            break;
        }
        if(i == e.length()-1){
            a = new Integer(atoi(e.c_str()));
            Integer *b = (Integer *)a;
            cout << b->getValue() << endl;
        }
    }
    return a;
}











                  
                  
                  
                  
                  
                  
