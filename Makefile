NAME = philo

INC = philo.h

SRC = philo.c error_function.c parse_input.c init_data.c monitor.c utils.c dinner.c destroy.c

CFLAG = gcc -Wall -Wextra -Werror -I -fsanitize=thread

all: $(NAME)

$(NAME) :
		$(CFLAG) $(INC) $(SRC) -o $(NAME)

fclean :
		rm -rf $(NAME)

re : fclean $(NAME)