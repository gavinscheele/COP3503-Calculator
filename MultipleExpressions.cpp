#include "MultipleExpressions.h"

MultipleExpressions::MultipleExpressions(string s){
    this->type = "multiple";
    this->expressions = s;
    this->exp = s;
    this->vectorExpressions = this->parseBySpaces(s);
}
MultipleExpressions::~MultipleExpressions(){
    delete this;
}
string MultipleExpressions:: getExpressions()
{
	string s = this->toString();
	return s;
}
Expression* MultipleExpressions::add(Expression* a)
{
    return this;
}

Expression* MultipleExpressions::subtract(Expression* a)
{
    return this;
}

Expression* MultipleExpressions::multiply(Expression* a)
{
    return this;
}

Expression* MultipleExpressions::divide(Expression* a)
{
    return this;
}
vector<string> MultipleExpressions::parseBySpaces(string expression){
    int count = 0;
    string temp = "";
    vector<string> expressions;
    for(int i = 0; i < expression.size(); i ++){       //creates an array of expressions and operations
        if (expression.at(i) == 'l' && expression.at(i+1) == 'o' && expression.at(i+2) == 'g') {
            for (int j = i; j < expression.size(); j++) {
                temp.push_back(expression.at(j));
                if (expression.at(j) == ')') {
                    i = j+1;
                    expressions.push_back(temp);
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
vector<string> MultipleExpressions::getVectorExpressions(){
    return this->vectorExpressions;
}

string MultipleExpressions:: toString(){
    stringstream s;
	s<<this->expressions;
	return s.str();
}

ostream& MultipleExpressions::print(std::ostream& output) const{
    output << expressions;
    return output;
}

