# ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>

class RPN
{
    private :

        std::string expr;
        std::string error_msg;
        std::stack<int>  stack;

    public :

        RPN();
        RPN(char *str);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        int process_expr();
        void do_operation(std::stack<int> &stack, char op);
        std::string get_error_msg() const;
        bool is_valid_op(char op);


};



# endif