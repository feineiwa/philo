NAME = philo

INC = philo.h

SRC = philo.c error_function.c parse_input.c init_data.c monitor.c utils.c

CFLAG = cc -Wall -Wextra -Werror -I

all: $(NAME)

$(NAME) :
		$(CFLAG) $(INC) $(SRC) -o $(NAME)

fclean :
		rm -rf $(NAME)

re : fclean $(NAME)