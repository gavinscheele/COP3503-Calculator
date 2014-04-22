//
//  Solver.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>


Solver::Solver(std::string a){
    this->localExpression = a;
    expressions = *new vector<string>();
    tokenStack = *new stack<string>();
    output = "";
}
Solver::~Solver(){
    
}
std::string Solver::solve(bool floatingPoint){

    this->expressions = this->parseBySpaces(localExpression);   //pass string to method and get a vector back with the expressions parsed by spaces
    
    shuntingYard(); //use shunting yard algorithm to put into correct order of operations without parenthesis

    this->expressions = this->parseBySpaces(output);    //parse new expression string by spaces
    
    if (floatingPoint) {                //if we are calculating the float value, call the float evaluation method
        return evaluateFloatString();
    }else
        return evaluateString();

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
                    if (!tokenStack.empty()) {
                        tokenStack.pop();
                    }else{
                        throw runtime_error("Error: Please check that the expression was entered properly");
                    }
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
                if (!tokenStack.empty()) {
                    tokenStack.pop();
                }else{
                    throw runtime_error("Error: Please check that the expression was entered properly");
                }
            }
            if (!tokenStack.empty()) {
                tokenStack.pop();
            }else{
                throw runtime_error("Error: Please check that the expression was entered properly");
            }
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
        stringstream s;
        s << this->bindToExpressionFloat(expressions.at(0));
        out = s.str();
        return out;
    }
    for(int i = 0; i < expressions.size(); i++){
        string token = expressions.at(i);
        
        if(!isAnOperator(token)){
            stk.push(token);
        }
        else{
            
            float e2 = bindToExpressionFloat(stk.top());
            stk.pop();
            
            float e1 = 0;
            if (i == 0) {
                e1 = bindToExpressionFloat(stk.top());
                stk.pop();
            }else{
                e1 = stof(stk.top());
                stk.pop();
            }

            
            //check function call and call appropriate method
            if(token == "+"){
                e1 += e2;
                stringstream s;
                s << e1;
                stk.push(s.str());
                out = s.str();
            }else if(token == "-"){
                e1 -= e2;
                stringstream s;
                s << e1;
                stk.push(s.str());
                out = s.str();
            }else if(token == "*"){
                e1 *= e2;
                stringstream s;
                s << e1;
                stk.push(s.str());
                out = s.str();
                
            }else if(token == "/"){
                e1 /= e2;
                stringstream s;
                s << e1;
                stk.push(s.str());
                out = s.str();
            }else if(token == "^"){
                for (int i = 1; i < e2; i++) {
                    e1 *= e1;
                    stringstream s;
                    s << e1;
                    stk.push(s.str());
                    out = s.str();
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
            if (stk.empty()) throw runtime_error("Error: Please check that the expression was entered properly");
            Expression* e2;
            e2 = bindToExpressionType(stk.top());
            e2->exp =  stk.top();
            stk.pop();

            if (stk.empty()) throw runtime_error("Error: Please check that the expression was entered properly");
            Expression *e1;
            e1 = bindToExpressionType(stk.top());
            e1->exp = stk.top();
            result = e1->exp;
            stk.pop();
            
            //check function call and call appropriate method
            if(token == "+"){
                if(e1->canAdd(e2)){
                    if (e1->type == "multiple") {
                      //  MultipleExpressions *d = (MultipleExpressions *)e1;
                      //  if (d->meType == "as") {
                            Expression *result = e1->add(e2);
                            stk.push(result->toString());
                            out = result->toString();
                      //  }else{
                        //    stk.push(e1->exp + " + " + e2->exp);
                          //  out = e1->toString() + " + " + e2->toString();
                       // }
                    }else if(e2->type == "multiple"){
                       // MultipleExpressions *d = (MultipleExpressions *)e2;
                       // if (d->meType == "as") {
                            Expression *result = e2->add(e1);
                            stk.push(result->toString());
                            out = result->toString();
                       // }else{
                         //   stk.push(e1->exp + " + " + e2->exp);
                           // out = e1->toString() + " + " + e2->toString();
                       // }
                    }else{
                        Expression *result = e1->add(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }else{
                    if (e2->type == "logarithm") {
                        Logarithm *a = (Logarithm *)e2;
                        a->simplify();
                        e2 = a;
                    }else{
                        stk.push(e1->exp + " + " + e2->exp);
                        out = e1->toString() + " + " + e2->toString();
                    }
                }
            }else if(token == "-"){
                if(e1->canSubtract(e2)){
                    
                    if (e1->type == "multiple") {
                       // MultipleExpressions *d = (MultipleExpressions *)e1;
                       // if (d->meType == "as") {
                            Expression *result = e1->subtract(e2);
                            stk.push(result->toString());
                            out = result->toString();
                       // }else{
                         //   stk.push(e1->exp + " - " + e2->exp);
                           // out = e1->toString() + " - " + e2->toString();
                        //}
                    }else if(e2->type == "multiple"){
                        //MultipleExpressions *d = (MultipleExpressions *)e2;
                        //if (d->meType == "as") {
                            Integer *t = new Integer(-1);
                            Expression *result1 = e2->multiply(t);
                            Expression *result = e2->add(result1);
                            delete t;
                            stk.push(result->toString());
                            out = result->toString();
                        //}else{
                          //  stk.push(e1->exp + " - " + e2->exp);
                            //out = e1->toString() + " - " + e2->toString();
                       // }
                    }else{
                        Expression *result = e1->subtract(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }else{
                    stk.push(e1->exp + " - " + e2->exp);
                    out = e1->toString() + " - " + e2->toString();
                }
            }else if(token == "*"){
                if (e2->type == "integer") {
                    Integer *t = (Integer *)e2;
                    if (t->getValue() == 1) {
                        stk.push(e1->toString());
                        out = e1->toString();
                    }else{
                        if (e1->canMultiply(e2)) {
                            Expression *result = e1->multiply(e2);
                            stk.push(result->toString());
                            out = result->toString();
                        }else{
                            stk.push(e1->exp + " * " + e2->exp);
                            out = e1->toString() + " * " + e2->toString();
                        }
                    }
                }else if(e1->type == "integer"){
                    Integer *t = (Integer *)e1;
                    if (t->getValue() == 1) {
                        stk.push(e2->toString());
                        out = e2->toString();
                    }else{
                        if (e2->canMultiply(e1)) {
                            Expression *result = e2->multiply(e1);
                            stk.push(result->toString());
                            out = result->toString();
                        }else{
                            stk.push(e2->exp + " * " + e1->exp);
                            out = e2->toString() + " * " + e1->toString();
                        }
                    }
                }
                else if(e1->canMultiply(e2)){
                    
                    if (e1->type == "multiple") {
                        //MultipleExpressions *d = (MultipleExpressions *)e1;
                        //if (d->meType == "md") {
                            Expression *result = e1->multiply(e2);
                            stk.push(result->toString());
                            out = result->toString();
                        //}else{
                          //  stk.push(e1->exp + " * " + e2->exp);
                          //  out = e1->toString() + " * " + e2->toString();
                        //}
                    }else if(e2->type == "multiple"){
                        //MultipleExpressions *d = (MultipleExpressions *)e2;
                        //if (d->meType == "md") {
                            Expression *result = e2->multiply(e1);
                            stk.push(result->toString());
                            out = result->toString();
                        //}else{
                          //  stk.push(e1->exp + " * " + e2->exp);
                            //out = e1->toString() + " * " + e2->toString();
                        //}
                    }else{
                        Expression *result = e1->multiply(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }else{
                    
                    stk.push(e1->exp + " * " + e2->exp);
                    out = e1->toString() + " * " + e2->toString();
                }
                

            }else if(token == "/"){
                if (e1->type == "integer" && e2->type == "integer") {
                    Integer *a = (Integer *)e1;
                    Integer *b = (Integer *)e2;
                    if(b->getValue() == 0) throw runtime_error("Error: Cannot Divide By Zero");
                    if (a->getValue() % b->getValue() != 0) {
                        e1 = new Rational(e1,e2);
                        stk.push(e1->toString());
                        out = e1->toString();
                    }else if(e1->canDivide(e2)){
                        Expression *result = e1->divide(e2);
                        stk.push(result->toString());
                        out = result->toString();
                    }
                }
                else if(e1->canDivide(e2)){
                    
                    if (e1->type == "multiple") {
                        //MultipleExpressions *d = (MultipleExpressions *)e1;
                        //if (d->meType == "md") {
                            Expression *result = e1->divide(e2);
                            stk.push(result->toString());
                            out = result->toString();
                        //}else{
                           // stk.push(e1->exp + " / " + e2->exp);
                           // out = e1->toString() + " / " + e2->toString();
                        //}
                    }else if(e2->type == "multiple"){
                        //MultipleExpressions *d = (MultipleExpressions *)e2;
                        //if (d->meType == "md") {
                            Rational *t = new Rational(new Integer(1),e1);
                            Expression *result = e2->multiply(t);
                            stk.push(result->toString());
                            out = result->toString();
                        //}else{
                          //  stk.push(e1->exp + " / " + e2->exp);
                            //out = e1->toString() + " / " + e2->toString();
                        //}
                    }else{
                    
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
                }
                else{
                    stk.push(e1->exp + " / " + e2->exp);
                    out = e1->toString() + " / " + e2->toString();

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
                    out = e1->toString();
                }else{
                    stk.push(e1->toString() + " ^ " + e2->toString());
                    out = e1->toString() + " ^ " + e2->toString();
                }


            }else{
                cout << "Error: Invalid Operator" << endl;
            }

        }

    }
    return out;
}
Expression* Solver::bindToExpressionType(string e){
    Expression *a = new MultipleExpressions("0");     //so the compiler doesnt complain. Will be set to appropriate type later
    for(int i = 0; i < e.length(); i++){
        if(e[i] == '*' || e[i] == '/' || e[i] == '+' || e[i] == '-'){
            if (e[i-1] == ' ' && e[i+1] == ' ') {
                a = new MultipleExpressions(e);
                return a;
            }
        }
    }
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
        }else if(e[i] == '^'){
            string before;
            string after;
            for(int j = 0; j < i; j++){
                before.push_back(e[j]);
            }
            for(int k = i+1; k < e.length(); k++){
                after.push_back(e[k]);
            }
            Expression *base = this->bindToExpressionType(before);
            Expression *exponent = this->bindToExpressionType(after);
            Rational *exp = new Rational(exponent,new Integer(1));
            a = new Exponential(base,exp);
            break;
        }
        else if(e[i] == 'p' && e[i+1] == 'i' && e[i+2] != '^' && e[i+3] != '^'){
            if (e[i-1] == '-') {
                a = new MultipleExpressions("-1 * pi");
            }else if(e[0] != 'p'){
                string coeff = "";
                for (int j = 0; j < e.length(); j++) {
                    if (e[j] == 'p') {
                        a = new MultipleExpressions(coeff + " * pi");
                    }else{
                        coeff += e[j];
                    }
                }
            }else{
                a = new Pi();
            }
            break;
        }else if(e[i] == 'e' && e[i+1] != '^'){
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
            for (int k = j+2; k < e.length()-1; k++) {
                if ((e[k] != '(' || e[k] != ')')) {
                    operand.push_back(e[k]);
                }
            }
            if (operand.at(operand.length()-1) == ' ') {
                operand.pop_back();
            }
            if (operand.at(0) == ' ') {
                operand.erase(0,1);
            }
            Expression *b = this->bindToExpressionType(base);
            Expression *o = this->bindToExpressionType(operand);
            if (b->type == "integer" && o->type == "integer") {
                Integer *ba = (Integer *)b;
                Integer *op = (Integer *)o;
                Logarithm *b = new Logarithm(ba->getValue(), op->getValue());
                Logarithm *c = (Logarithm *)b->simplify();
                if(c->type == "multiple"){
                    a = bindToExpressionType(c->exp);
                    break;
                }
                a = c;
            }else{
                Logarithm *c = new Logarithm(b,o);
                a = c->simplify();
            }
            break;
        }else if(e[i] == 'r' && e[i+1] == 't' & e[i+2] == ':'){
            string root;
            string operand;
            Expression *rt;
            Expression *op;
            if(e[i-1] == 'q' && e[i-2] == 's'){
                int k = i + 3;
                while (k < e.length()) {
                    operand.push_back(e[k]);
                    k++;
                }
                rt = new Integer(2);
                op = this->bindToExpressionType(operand);
                a = new nthRoot(2,op,1);
                
            }else{
                int j = 0;
                while (e[j] != 'r') {
                    root.push_back(e[j]);
                    j++;
                }
                j = i+3;
            
                while (j < e.length()) {
                    operand.push_back(e[j]);
                    j++;
                }
                rt = this->bindToExpressionType(root);
                op = this->bindToExpressionType(operand);
                //create a new rational with these types
            }
            if (rt->type == "integer" && op->type == "integer") {
                Integer *c = (Integer *)rt;
                Integer *d = (Integer *)op;
                a = new nthRoot(c->getValue(),d->getValue(),1);
            }
            break;
        }
        else if(!isdigit(e[i]) && e[i] != '-' && e[i] != 'e' && e[i] != 'p' && e[i] != 'i' && e[i] != ' ' && e[i] != 's' && e[i] != 'q'){
            break;
        }
        else if(i == e.length()-1){
            a = new Integer(atoi(e.c_str()));
        }
    }
    if(dynamic_cast<MultipleExpressions *>(a) != 0 && a->exp == "0"){
        stringstream s;
        s << "Could not bind '" << e << "' to a type" << "\n";
        s << "Please make sure that each of your operations and operands are seperated by a space";
        throw runtime_error(s.str());
    }
    return a;
}
float Solver::bindToExpressionFloat(string e){
         //so the compiler doesnt complain. Will be set to appropriate type later
    float a = 0;
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
            cout << atof(before.c_str()) << endl;
            cout << atof(after.c_str()) << endl;
            a = atof(before.c_str()) / atof(after.c_str());
            break;
        }else if(e[i] == 'p' && e[i+1] == 'i'){
            a = M_PI;
            break;
        }else if(e[i] == 'e'){
            a = M_E;
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
                if (e[k] != '(' || e[k] != ')') {
                    operand.push_back(e[k]);
                }
            }
            float b = this->bindToExpressionFloat(base);
            float o = this->bindToExpressionFloat(operand);
            if (b == 10) {
                a = log10f(o);
            }else if(b == 2){
                a = log2f(o);
            }else if(b == M_E){
                a = logf(o);
            }else{
                a = log10f(o)/log10f(b);
            }
            break;
        }
        else if(!isdigit(e[i]) && e[i] != '-'){
            break;
        }
        else if(i == e.length()-1){
            a = atoi(e.c_str());
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

vector<string> Solver::parseBySpaces(string expression){
    int count = 0;
    string temp = "";
    vector<string> expressions = *new vector<string>();
    for(int i = 0; i < expression.size(); i ++){       //creates an array of expressions and operations
        if (expression.at(i) == 'l' && expression.at(i+1) == 'o' && expression.at(i+2) == 'g') {
            temp = "";
            for (int j = i; j < expression.size(); j++) {
                temp.push_back(expression.at(j));
                if (expression.at(j) == ')') {
                    i = j+1;
                    expressions.push_back(temp);
                    count = j + 2;
                    break;
                }
            }
        }
        else if(expression.at(i) == ' '){
            temp = "";
            for (int j = count; j < i; j++) {
                temp.push_back(expression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
            
        }else if(i == expression.size()-1){
            temp = "";
            for (int j = count; j <= i; j++) {
                temp.push_back(expression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
        }
    }
    return expressions;
}















