# ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <unistd.h>
# include <string>
# include <cstdlib>


class BitcoinExchange
{
    private :

        std::string error_msg;
        std::map<std::string, float>   dbmap;

    public :

        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        int open_file(const char *file_name);
        int load_db();
        int load_input_file(char *file_name);
        bool parsedbline(std::string &line, std::string &date, float &rate, char del);
        void ft_remove_whitespaces(std::string& s);
        bool is_valid_date(std::string &date);
        bool is_valid_price(float &rate, std::string &rate_str, char del);


};


# endif