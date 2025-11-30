# include "RPN.hpp"

int main(int arc, char **arv)
{
    if (arc == 2)
    {
        RPN proccessor(arv[1]);

        if (proccessor.process_expr())
        {
            std::cerr << proccessor.get_error_msg() << std::endl;
            return 1;
        }
        return 0;
    }
    else
        std::cerr << "Error : Usage <mathematical expression>" << std::endl;
    return 1;
}