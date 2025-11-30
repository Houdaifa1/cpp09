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

bool RPN::do_operation(std::stack<int> &stack, char op)
{
    if (stack.size() < 2)
    {
        error_msg = "Error : Not enough numbers to do an operation!";
        return false;
    }
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
        if (second == 0)
        {
            error_msg = "Error : Can't divide by 0!";
            return false;
        }
        stack.push(first / second);
        break;
    case '*':
        stack.push(first * second);
        break;
    }
    return true;
}

bool RPN::is_valid_op(char op)
{
    if (op == '+' || op == '-' || op == '/' || op == '*')
        return true;
    return false;
}

int RPN::process_expr()
{
    while (!stack.empty())
        stack.pop();

    std::stringstream ss(expr);
    std::string token;
    while (ss >> token)
    {

        if (token.size() == 1 && isdigit(token[0]))
            stack.push(token[0] - 48);
        else if (token.size() == 1 && is_valid_op(token[0]))
        {
            if (!do_operation(stack, token[0]))
                return 1;
        }
        else if (token.size() > 1)
        {
            error_msg = "Error: invalid token must be single-digit or operator!";
            return 1;
        }
        else
        {
            error_msg = "Error : Unknown Character : " + token;
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
