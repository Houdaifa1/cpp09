# ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <stdexcept>
# include <limits>
# include <ctime>
# include <algorithm>
#include <iomanip>


class PmergeMe
{

    private :

        std::vector<int>    vec_cont;
        std::deque<int>     deq_cont;

        std::vector<std::pair<int, int> > vec_pairs;
        std::deque<std::pair<int, int> > deq_pairs;

        bool vec_has_straggler;
        bool deq_has_straggler;
        
        int vec_straggler_val;
        int deq_straggler_val;

        void make_vec_pairs();
        void make_deq_pairs();

        std::vector<std::pair<int, int> > sort_pairs(const std::vector<std::pair<int, int> > &vec_pairs);

        std::vector<size_t> generate_jacobsthal(size_t n);
        void insert_pending_ford_johnson(std::deque<int> &main_chain, const std::deque<int> &pend_chain);
        void insert_pending_ford_johnson(std::vector<int> &main_chain, const std::vector<int> &pend_chain);

    public :

        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        class Error : public std::exception
        {
            public :
                virtual const char *what() const throw();
        };

        void sort(char **nbrs, int size);
        void pars_num(std::string num_str, int &num);


};


# endif