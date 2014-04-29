#ifndef MULTIPLEEXPRESSIONS_H_INCLUDED
#define MULTIPLEEXPRESSIONS_H_INCLUDED

#include <iostream>
#include "Expression.h"
#include "Exponential.h"
#include "Logarithm.h"
#include "Integer.h"
#include "Rational.h"
#include "Solver.h"
#include <sstream>
using namespace std;

class MultipleExpressions : public Expression{
public:
    MultipleExpressions(string s);
    ~MultipleExpressions();
    string toString();
	string getExpressions();
    ostream& print(std::ostream& output) const;
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    vector<string> getVectorExpressions();
    
    bool canAdd(Expression* b);
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);
    
    string meType;
private:
    string expressions;
    vector<string> vectorExpressions;
    vector<string> parseBySpaces(string expression);
    MultipleExpressions* foil(Expression *one, string operation1, Expression *two, Expression *three, string operation2, Expression *four);

};


#endif // MULTIPLELOGS_H_INCLUDED
