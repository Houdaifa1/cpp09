# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : dbmap(other.dbmap)
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        dbmap = other.dbmap;
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::ft_remove_whitespaces(std::string& s)
{
    size_t start = 0;
    while (start < s.size() && ((s[start] >= 9 && s[start] <= 13) || s[start] == ' '))
        ++start;
    size_t end = s.size();
    while (end > start && ((s[end - 1] >= 9 && s[end - 1] <= 13) || s[end - 1] == ' '))
        --end;
    s = s.substr(start, end - start);
}

int BitcoinExchange::open_file(const char *file_name)
{
    if (access(file_name, F_OK) != 0)
    {
        std::cerr << "Error File Not Found: " << file_name << std::endl;
        return 1; 
    }
    if (access(file_name, R_OK) != 0)
    {
        std::cerr << "Error Unable to open file: " << file_name << std::endl;
        return 1; 
    }
    return 0;
}

bool  BitcoinExchange::is_valid_date(std::string &date)
{
    ft_remove_whitespaces(date);
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if(!isdigit(date[i]))
            return false;
    }
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (!(month >= 1 && month <= 12))
        return false;
    int days_in_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1 || day > days_in_month[month - 1])
        return false;
    return true;
}

bool  BitcoinExchange::is_valid_price(float &rate, std::string &rate_str, char del)
{
    ft_remove_whitespaces(rate_str);
    if (rate_str.empty())
    {
        error_msg =  "Error: Number not found.";
        return false;
    }
    int dot_count = 0;
    size_t dot_pos = 0;
    for(size_t i = 0; i < rate_str.size(); i++)
    {
        if (rate_str[0] == '-')
        {
            error_msg =  "Error: not a positive number.";
            return false;
        }
        if (rate_str[i] == '.')
        {
            dot_count++;
            dot_pos = i;
            continue;
        }
        if (!isdigit(rate_str[i]))
        {
            error_msg =  "Error: Non numeric character found.";
            return false;
        }
    }
    if (dot_count == 0)
        rate = std::strtof(rate_str.c_str(), NULL);
    else if (dot_count != 1 || rate_str.size() < 3 || dot_pos == 0 || dot_pos == rate_str.size() - 1
        || !isdigit(rate_str[dot_pos - 1]) || !isdigit(rate_str[dot_pos + 1]))
    {
        error_msg =  "Error: Wrong format for a number.";
        return false;
    }
    else
        rate = std::strtof(rate_str.c_str(), NULL);
    if (del == '|' && rate > 1000)
    {
        error_msg = "Error: too large a number.";
        return false;
    }
    return true;
}

bool BitcoinExchange::parsedbline(std::string &line, std::string &date, float &rate, char del)
{
    size_t del_pos = line.find(del);
    if (del_pos == std::string::npos)
    {
        error_msg = "Error: bad input => ";
        error_msg += line;
        return false;
    }
    date = line.substr(0, del_pos);
    if (!is_valid_date(date))
    {
        error_msg = "Error: bad input => ";
        error_msg += date;
        return false;
    }
    std::string rate_str = line.substr(del_pos + 1);
    if (!is_valid_price(rate, rate_str, del))
        return false;
    return true;
}

int BitcoinExchange::load_db()
{
    if (open_file("data.csv"))
        return 1;
    std::fstream db_file("data.csv");

    std::string line;
    std::string date;
    float       rate;
    std::getline(db_file, line);
    while(std::getline(db_file, line))
    {
        if (parsedbline(line, date, rate, ','))
            dbmap.insert(std::make_pair(date, rate));
    }
    return 0;
}

int BitcoinExchange::load_input_file(char *file_name)
{
    if (open_file(file_name))
        return 1;
    std::fstream db_file(file_name);

    std::string line;
    std::string date;
    float       price;
    std::getline(db_file, line);
    if (dbmap.begin() == dbmap.end())
            return 0;
    while(std::getline(db_file, line))
    {
        
        if (parsedbline(line, date, price, '|'))
        {
            std::map<std::string, float>::iterator it = dbmap.lower_bound(date);
            if (it == dbmap.begin() && it->first > date)
            {
                std::cerr << "Error : Date not found." << std::endl;
                continue;
            }
            if (it != dbmap.begin() && it->first != date)
                it--;
            std::cout << date << " => " << price << " = " << price * it->second << std::endl;
        }
        else
            std::cerr << error_msg << std::endl;
    }
    return 0;

}
