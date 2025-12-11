#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN <RPN expression>" << std::endl;
        return 1;
    }

    RPN processor(argv[1]);
    if (processor.process_expr())
    {
        std::cerr << processor.get_error_msg() << std::endl;
        return 1;
    }
    return 0;
}
