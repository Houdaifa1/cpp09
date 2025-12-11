# include "PmergeMe.hpp"

int main (int arc, char **arv)
{
    if (arc < 2)
    {
        std::cerr << "Usage: ./PmergeMe <positive integer sequence>" << std::endl;
        return 1;
    }

    PmergeMe frd_jsn;
    try 
    {
        frd_jsn.sort(arv, arc);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }

}