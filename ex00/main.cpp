# include "BitcoinExchange.hpp"

int main(int arc, char **arv)
{
    if (arc == 2)
    {
        BitcoinExchange btc;
        if (btc.load_db())
            return 1;
        if (btc.load_input_file(arv[1]))
            return 1;
    }
    else
        std::cerr << "Wrong Usage : ./btc <input_file>\n";
}