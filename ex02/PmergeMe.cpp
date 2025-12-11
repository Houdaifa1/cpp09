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



std::vector<std::pair<int, int> > PmergeMe::sort_pairs(const std::vector<std::pair<int, int> >& pairs)
{
    if (pairs.size() <= 1)
        return pairs;
    
    size_t mid = pairs.size() / 2;
    
    std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::vector<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());
    
    std::vector<std::pair<int, int> > sorted_left = sort_pairs(left);
    std::vector<std::pair<int, int> > sorted_right = sort_pairs(right);
    
    std::vector<std::pair<int, int> > merged;
    merged.reserve(pairs.size());
    
    size_t i = 0, j = 0;
    while (i < sorted_left.size() && j < sorted_right.size())
    {
        if (sorted_left[i].second < sorted_right[j].second)
            merged.push_back(sorted_left[i++]);
        else
            merged.push_back(sorted_right[j++]);
    }
    
    while (i < sorted_left.size())
        merged.push_back(sorted_left[i++]);
    while (j < sorted_right.size())
        merged.push_back(sorted_right[j++]);
    
    return merged;
}

std::vector<size_t> PmergeMe::generate_jacobsthal(size_t n)
{
    std::vector<size_t> jac;
    if (n == 0)
        return jac;
    jac.push_back(0);
    if (n == 1)
        return jac;
    jac.push_back(1);
    while (jac.size() < n)
    {
        size_t sz = jac.size();
        size_t next = jac[sz - 1] + 2 * jac[sz - 2];
        jac.push_back(next);
    }
    return jac;
}

void PmergeMe::insert_pending_ford_johnson(std::vector<int> &main_chain, const std::vector<int> &pend_chain)
{
    std::vector<size_t> jacob = generate_jacobsthal(pend_chain.size());
    std::vector<bool> used(pend_chain.size(), false);

    for (size_t i = 1; i < jacob.size(); ++i)
    {
        size_t idx = jacob[i] - 1;   
        if (idx < pend_chain.size() && !used[idx])
        {
            std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), pend_chain[idx]);
            main_chain.insert(it, pend_chain[idx]);
            used[idx] = true;
        }
    }

    for (size_t i = pend_chain.size(); i-- > 0; )
    {
        if (!used[i])
        {
            std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), pend_chain[i]);
            main_chain.insert(it, pend_chain[i]);
        }
    }
}




void PmergeMe::make_vec_pairs()
{
    vec_pairs.clear();
    size_t pair_count = vec_cont.size() / 2;

    vec_has_straggler = (vec_cont.size() % 2);
    if (vec_has_straggler)
        vec_straggler_val = vec_cont.back();

    for (size_t i = 0; i < (pair_count * 2) ; i+=2)
    {
        int a = vec_cont[i];
        int b = vec_cont[i + 1];
        vec_pairs.push_back(std::make_pair(
            std::min(a, b),
            std::max(a, b)
        ));
    }

    vec_pairs = sort_pairs(vec_pairs);

    std::vector<int> main_chain, pend_chain;
    for (size_t i = 0; i < vec_pairs.size(); i++)
    {
        pend_chain.push_back(vec_pairs[i].first);
        main_chain.push_back(vec_pairs[i].second);       
    }

    insert_pending_ford_johnson(main_chain, pend_chain);

    if (vec_has_straggler)
    {
        std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), vec_straggler_val);
        main_chain.insert(it, vec_straggler_val);
    }

    vec_cont.assign(main_chain.begin(), main_chain.end());
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

void PmergeMe::sort(char **nbrs, int size)
{
    for (int i = 1; i < size; i++)
    {
        int num;
        pars_num(nbrs[i], num);
        if ((std::find(vec_cont.begin(), vec_cont.end(), num)) == vec_cont.end())
            vec_cont.push_back(num);
        if ((std::find(deq_cont.begin(), deq_cont.end(), num)) == deq_cont.end())
            deq_cont.push_back(num);
    }
    std::cout << "Before: ";
    for (size_t i = 0; i < vec_cont.size(); ++i)
        std::cout << vec_cont[i] << ' ';
    std::cout << std::endl;

   
    std::clock_t start_vec = std::clock();
    make_vec_pairs();
    double time_vec = static_cast<double>(std::clock() - start_vec) / CLOCKS_PER_SEC * 1000;

    std::clock_t start_deq = std::clock();
    make_deq_pairs();
    double time_deq = static_cast<double>(std::clock() - start_deq) / CLOCKS_PER_SEC * 1000;

    std::cout << "After: ";
    for (size_t i = 0; i < vec_cont.size(); ++i)
        std::cout << vec_cont[i] << ' ';
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5); 
    std::cout << "Time to process a range of " << vec_cont.size() 
              << " elements with std::vector : " << time_vec << " us" << std::endl;

    std::cout << "Time to process a range of " << deq_cont.size() 
              << " elements with std::deque : " << time_deq << " us" << std::endl;
  
}

void PmergeMe::insert_pending_ford_johnson(std::deque<int> &main_chain, const std::deque<int> &pend_chain)
{
    std::vector<size_t> jacob = generate_jacobsthal(pend_chain.size());
    std::vector<bool> used(pend_chain.size(), false);

    for (size_t i = 1; i < jacob.size(); ++i)
    {
        size_t idx = jacob[i] - 1;
        if (idx < pend_chain.size() && !used[idx])
        {
            std::deque<int>::iterator it = 
                std::lower_bound(main_chain.begin(), main_chain.end(), pend_chain[idx]);
            main_chain.insert(it, pend_chain[idx]);
            used[idx] = true;
        }
    }

    for (size_t i = pend_chain.size(); i-- > 0;)
    {
        if (!used[i])
        {
            std::deque<int>::iterator it =
                std::lower_bound(main_chain.begin(), main_chain.end(), pend_chain[i]);
            main_chain.insert(it, pend_chain[i]);
        }
    }
}

void PmergeMe::make_deq_pairs()
{
    deq_pairs.clear();

    size_t pair_count = deq_cont.size() / 2;

    deq_has_straggler = (deq_cont.size() % 2);
    if (deq_has_straggler)
        deq_straggler_val = deq_cont.back();

    for (size_t i = 0; i < pair_count * 2; i += 2)
    {
        int a = deq_cont[i];
        int b = deq_cont[i + 1];
        deq_pairs.push_back(std::make_pair(
            std::min(a, b),
            std::max(a, b)
        ));
    }

    std::vector<std::pair<int,int> > temp_pairs(deq_pairs.begin(), deq_pairs.end());
    temp_pairs = sort_pairs(temp_pairs);
    deq_pairs.assign(temp_pairs.begin(), temp_pairs.end());

    std::deque<int> main_chain, pend_chain;

    for (size_t i = 0; i < deq_pairs.size(); ++i)
    {
        pend_chain.push_back(deq_pairs[i].first);
        main_chain.push_back(deq_pairs[i].second);
    }

 
    insert_pending_ford_johnson(main_chain, pend_chain); 

    if (deq_has_straggler)
    {
        std::deque<int>::iterator it =
            std::lower_bound(main_chain.begin(), main_chain.end(), deq_straggler_val);
        main_chain.insert(it, deq_straggler_val);
    }

    deq_cont.assign(main_chain.begin(), main_chain.end());
}