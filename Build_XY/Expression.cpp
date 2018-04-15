#include "Expression.h"
#include "Operations.h"

static map<string, Unary> unaryFuncs;
static map<string, Binary> binaryFuncs;

void initOperations()
{
	unaryFuncs["plus"] = &unaryPlus;
	unaryFuncs["minus"] = &unaryMinus;
	unaryFuncs["abs"] = &abs;
	unaryFuncs["sqrt"] = &sqrt;
	unaryFuncs["log"] = &log2;
	unaryFuncs["sin"] = &sin;
	unaryFuncs["cos"] = &cos;
	unaryFuncs["tg"] = &tg;
	unaryFuncs["ctg"] = &ctg;
	binaryFuncs["+"] = &addition;
	binaryFuncs["-"] = &subtraction;
	binaryFuncs["*"] = &multiplication;
	binaryFuncs["/"] = &division;
	binaryFuncs["%"] = &modulo;
	binaryFuncs["^"] = &exponentiation;
}

Block::Block(double value)
{
	type = VALUE;
	this->value = value;
}
Block::Block(const string& variable)
{
	type = VARIABLE;
	this->variable = variable;
}
Block::Block(Unary unary)
{
	type = UNARY;
	this->unary = unary;
}
Block::Block(Binary binary)
{
	type = BINARY;
	this->binary = binary;
}
int getPrior(const string& oper)
{
	if (oper == "+" || oper == "-")
		return 1;
	if (oper == "*" || oper == "/")
		return 2;
	if (oper == "^")
		return 3;
	return 4;
}
bool isRightAssoc(const string& oper)
{
	return oper == "^";
}
vector<Block> toRPN(const string& expr)
{
	vector<Block> res;
	vector<string> opers;
	bool mayUnary = 1;
	for (int i = 0; i < expr.size(); i++)
	{
		if (expr[i] == '(')
		{
			opers.push_back("(");
			mayUnary = 1;
			continue;
		}
		if (expr[i] == ')')
		{
			while (opers.back() != "(")
			{
				res.push_back(Block(binaryFuncs[opers.back()]));
				opers.pop_back();
			}
			opers.pop_back();
			while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4)
			{
				res.push_back(Block(unaryFuncs[opers.back()]));
				opers.pop_back();
			}
			mayUnary = 0;
			continue;
		}
		int it = i + 1;
		if (isdigit(expr[i]) || expr[i] == '.')
		{
			while (it < expr.size() && (isdigit(expr[it]) || expr[it] == '.'))
				it++;
		}
		if (isalpha(expr[i]))
		{
			while (it < expr.size() && isalpha(expr[it]))
				it++;
		}
		string block = substr(expr, i, it - 1);
		i = it - 1;
		if (isdigit(block[0]) || block[0] == '.')
		{
			res.push_back(Block(stod(block)));
			while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4)
			{
				res.push_back(Block(unaryFuncs[opers.back()]));
				opers.pop_back();
			}
			mayUnary = 0;
			continue;
		}
		if (mayUnary && block == "+")
			block = "plus";
		if (mayUnary && block == "-")
			block = "minus";
		if (!unaryFuncs.count(block) && !binaryFuncs.count(block))
		{
			res.push_back(Block(block));
			while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4)
			{
				res.push_back(Block(unaryFuncs[opers.back()]));
				opers.pop_back();
			}
			mayUnary = 0;
			continue;
		}
		if (getPrior(block) != 4)
		{
			while (!opers.empty() && opers.back() != "(" && (isRightAssoc(block) && getPrior(block) < getPrior(opers.back()) || !isRightAssoc(block) && getPrior(block) <= getPrior(opers.back())))
			{
				res.push_back(Block(binaryFuncs[opers.back()]));
				opers.pop_back();
			}
		}
		mayUnary = 1;
		opers.push_back(block);
	}
	while (!opers.empty())
	{
		res.push_back(Block(binaryFuncs[opers.back()]));
		opers.pop_back();
	}
	return res;
}

bool calc(double& res, const vector<Block>& sequence, const map<string, double>& vars)
{
	vector<double> stck;
	for (int i = 0; i < sequence.size(); i++)
	{
		if (sequence[i].type == Block::VALUE)
			stck.push_back(sequence[i].value);
		if (sequence[i].type == Block::VARIABLE)
			stck.push_back(vars.at(sequence[i].variable));
		if (sequence[i].type == Block::UNARY)
		{
			double x = stck.back();
			stck.pop_back();
			double res;
			if (!sequence[i].unary(res, x))
				return 0;
			stck.push_back(res);
		}
		if (sequence[i].type == Block::BINARY)
		{
			double b = stck.back();
			stck.pop_back();
			double a = stck.back();
			stck.pop_back();
			double res;
			if (!sequence[i].binary(res, a, b))
				return 0;
			stck.push_back(res);
		}
	}
	res = stck[0];
	return 1;
}

static const double M_E = 2.71828182845904523536;
Expression::Expression()
{ }
Expression::Expression(const string& expr)
{
	sequence = toRPN(expr);
	variables["e"] = M_E;
}
void Expression::setVariable(const string& variable, double value)
{
	variables[variable] = value;
}
bool Expression::consider(double& res) const
{
	return calc(res, sequence, variables);
}