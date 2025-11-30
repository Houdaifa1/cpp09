NAME = RPN

CC = c++

CFLAGS = -Wall -Wextra -Werror 

SRCS = main.cpp RPN.cpp

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS)$(SRCS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all