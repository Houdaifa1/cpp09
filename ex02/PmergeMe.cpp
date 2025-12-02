# include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &other) : vec_cont(other.vec_cont),
                                            deq_cont(other.deq_cont){}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec_cont = other.vec_cont;
        deq_cont = other.deq_cont;
    }
    return *this;
}


const char *PmergeMe::Error::what() const throw()
{
    return "Error\n";
}


void PmergeMe::make_vec_pairs()
{
    int pair_count = vec_cont.size() / 2;

    if ((vec_cont.size() % 2) == 1)
    {
        vec_has_straggler = true;
        vec_straggler_val = vec_cont[vec_cont.size() - 1];
    }
    else
        vec_has_straggler = false;
    for (int i = 0; i < (pair_count * 2) ; i+=2)
    {
        int first, second;
        vec_cont[i] < vec_cont[i + 1] ? first = vec_cont[i], second = vec_cont[i + 1] :
                    first = vec_cont[i + 1], second = vec_cont[i];  
        std::pair<int, int> pair;
        pair.first = first;
        pair.second = second;
        vec_pairs.push_back(pair);
    }

}

void PmergeMe::make_deq_pairs()
{
    int pair_count = deq_cont.size() / 2;

    if ((deq_cont.size() % 2) == 1)
    {
        deq_has_straggler = true;
        deq_straggler_val = deq_cont[deq_cont.size() - 1];
    }
    else
        deq_has_straggler = false;
    for (int i = 0; i < (pair_count * 2) ; i+=2)
    {
        int first, second;
        deq_cont[i] < deq_cont[i + 1] ? first = deq_cont[i], second = deq_cont[i + 1] :
                    first = deq_cont[i + 1], second = deq_cont[i];  
        std::pair<int, int> pair;
        pair.first = first;
        pair.second = second;
        deq_pairs.push_back(pair);
    }
}


void PmergeMe::pars_num(std::string num_str, int &num)
{
    if (num_str.empty())
        throw PmergeMe::Error();

    long res = 0;
    int count = 0;

    size_t i = 0;

    while(num_str[i] == '0')
        i++;

    for (; i < num_str.size(); i++)
    {
        if (!isdigit(num_str[i]))
            throw PmergeMe::Error();
        
        count++;
        if (count > 10)
            throw PmergeMe::Error();
        res = res * 10 + (num_str[i] - 48);
    }

    if (res > std::numeric_limits<int>::max())
        throw PmergeMe::Error();
    num = static_cast<int> (res);
}

void PmergeMe::load_containers(char **nbrs, int size)
{
    for (int i = 0; i < size; i++)
    {
        int num;
        pars_num(nbrs[i], num);
        if ((std::find(vec_cont.begin(), vec_cont.end(), num)) == vec_cont.end())
            vec_cont.push_back(num);
        if ((std::find(deq_cont.begin(), deq_cont.end(), num)) == deq_cont.end())
            deq_cont.push_back(num);
    }
}