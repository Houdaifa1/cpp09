# ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <stdexcept>
# include <limits>
# include <algorithm>

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

        void load_containers(char **nbrs, int size);
        void pars_num(std::string num_str, int &num);


};


# endif