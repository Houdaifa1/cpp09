NAME = btc

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp BitcoinExchange.cpp

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all