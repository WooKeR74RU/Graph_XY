#include "Expression.h"

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

bool isOperation(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}
bool isRightAssoc(const string& oper)
{
	return oper == "^";
}
int getPrior(const string& oper)
{
	if (oper.size() > 1)
		return 3;
	if (oper == "+" || oper == "-")
		return 0;
	if (oper == "*" || oper == "/" || oper == "%")
		return 1;
	if (oper == "^")
		return 2;
}
void addFunc(vector<Block>& sequence, const string& oper)
{
	if (unaryFuncs.count(oper))
		sequence.push_back(Block(unaryFuncs[oper]));
	if (binaryFuncs.count(oper))
		sequence.push_back(Block(binaryFuncs[oper]));
}

vector<Block> toRPN(const string& expr)
{
	vector<Block> res;
	bool mayUnary = 1;
	vector<string> opers;
	for (int i = 0; i < expr.length(); i++)
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
				addFunc(res, opers.back());
				opers.pop_back();
			}
			opers.pop_back();
			mayUnary = 0;
			continue;
		}
		bool isFunc = 0;
		string block;
		if (isalpha(expr[i]))
		{
			int it = i;
			while (it < expr.size() && isalpha(expr[it]))
				it++;
			block = substr(expr, i, it - 1);
			i = it - 1;
			if (unaryFuncs.count(block) || binaryFuncs.count(block))
				isFunc = 1;
		}
		if (isOperation(expr[i]))
		{
			if (mayUnary)
			{
				if (expr[i] == '-')
					block = "minus";
				else
					block = "plus";
			}
			else
			{
				block = to_string(expr[i]);
			}
			isFunc = 1;
		}
		if (isdigit(expr[i]) || expr[i] == '.')
		{
			int it = i;
			while (it < expr.size() && (isdigit(expr[it]) || expr[it] == '.'))
				it++;
			block = substr(expr, i, it - 1);
			i = it - 1;
		}
		if (isFunc)
		{
			while (!opers.empty() && (!isRightAssoc(block) && getPrior(opers.back()) >= getPrior(block) || isRightAssoc(block) && getPrior(opers.back()) > getPrior(block)))
			{
				addFunc(res, opers.back());
				opers.pop_back();
			}
			opers.push_back(block);
			mayUnary = 1;
		}
		else
		{
			if (isdigit(expr[i]))
				res.push_back(Block(stod(block)));
			else
				res.push_back(Block(block));
			mayUnary = 0;
		}
	}
	while (!opers.empty())
	{
		addFunc(res, opers.back());
		opers.pop_back();
	}
	return res;
}
bool calc(double& res, const vector<Block>& sequence, const map<string, double>& variables)
{
	vector<double> stck;
	for (int i = 0; i < sequence.size(); i++)
	{
		if (sequence[i].type == Block::VALUE)
			stck.push_back(sequence[i].value);
		if (sequence[i].type == Block::VARIABLE)
			stck.push_back(variables.at(sequence[i].variable));
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

Expression::Expression(const string& expr)
{
	sequence = toRPN(expr);
}
bool Expression::consider(double& res, const map<string, double>& variables) const
{
	return calc(res, sequence, variables);
}