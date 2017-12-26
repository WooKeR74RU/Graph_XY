#pragma once
#include "Utilities.h"
#include "Operations.h"

typedef bool(*Unary)(double&, double);
static map<string, Unary> unaryFuncs;
typedef bool(*Binary)(double&, double, double);
static map<string, Binary> binaryFuncs;

void initOperations();

struct Block
{
	enum BlockType { VALUE, VARIABLE, UNARY, BINARY } type;
	double value;
	string variable;
	Unary unary;
	Binary binary;
	Block(double value);
	Block(const string& variable);
	Block(Unary unary);
	Block(Binary binary);
};

bool isOperation(char c);
bool isRightAssoc(const string& oper);
int getPrior(const string& oper);
void addFunc(vector<Block>& sequence, const string& oper);

vector<Block> toRPN(const string& expr);
bool calc(double& res, const vector<Block>& sequence, const map<string, double>& variables);

struct Expression
{
private:
	vector<Block> sequence;
public:
	Expression(const string& expr);
	bool consider(double& res, const map<string, double>& variables) const;
};