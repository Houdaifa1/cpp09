#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(char *str) : expr(str) {}

RPN::RPN(const RPN &other) : expr(other.expr), error_msg(other.error_msg) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        expr = other.expr;
        error_msg = other.error_msg;
    }
    return *this;
}

std::string RPN::get_error_msg() const
{
    return error_msg;
}

void RPN::do_operation(std::stack<int> &stack, char op)
{

    int second = stack.top();
    stack.pop();
    int first = stack.top();
    stack.pop();
    switch (op)
    {
    case '-':
        stack.push(first - second);
        break;
    case '+':
        stack.push(first + second);
        break;
    case '/':
        stack.push(first / second);
        break;
    case '*':
        stack.push(first * second);
        break;
    }
}

bool RPN::is_valid_op(char op)
{
    if (op == '+' || op == '-' || op == '/' || op == '*')
        return true;
    return false;
}

int RPN::process_expr()
{
    for (size_t i = 0; i < expr.size(); i++)
    {
        if (isdigit(expr[i]))
        {
            if (i + 1 < expr.size() - 1 && isdigit(expr[i + 1]))
            {
                error_msg = "Error : expect a single digit number!";
                return 1;
            }
            stack.push(expr[i] - 48);
        }
        else if (is_valid_op(expr[i]))
        {
            if (stack.size() < 2)
            {
                error_msg = "Error : Not enough numbers to do an operation!";
                return 1;
            }
            if (i + 1 < expr.size() - 1 && is_valid_op(expr[i + 1]))
            {
                error_msg = "Error : expect a single operation!";
                return 1;
            }
            do_operation(stack, expr[i]);
        }
        else if (expr[i] == ' ')
            continue;
        else
        {
            error_msg = "Error : not a valid character!";
            return 1;
        }
    }
    if (stack.size() != 1)
    {
        error_msg = "Error : stack must contain ONE number at the end";
        return 1;
    }
    std::cout << stack.top() << std::endl;
    return 0;
}
