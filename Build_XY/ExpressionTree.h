#pragma once
#include "Utilities.h"
#include "Operations.h"

typedef bool(*singleMathFunc)(double&, double);
static map<string, singleMathFunc> singleFuncs;
typedef bool(*doubleMathFunc)(double&, double, double);
static map<char, doubleMathFunc> doubleFuncs;
void initOperations();

struct Node
{
	typedef Node* Ptr;
	int type;
	//Type 0 - Value
	double value;
	//Type 1 - X
	//Type 2 - Single function
	singleMathFunc singleFunc;
	Ptr firstVal;
	//Type 3 - Double function
	doubleMathFunc doubleFunc;
	Ptr secondVal;
	Node(double val);
	Node();
	Node(singleMathFunc func, Ptr val);
	Node(doubleMathFunc func, Ptr first, Ptr second);
	bool consider(double& res, double x) const;
};

Node::Ptr buildExpressionTree(const string& expr);

class Function
{
public:
	Node::Ptr expressionTreeRoot;
	Function(const Node::Ptr& expressionTreeRoot);
	Function(const string& expr);
	bool consider(double& res, double x) const;
};