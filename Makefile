NAME = philo

INC = -I./inc/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/

OBJ_DIR = obj/

SRCS = philo.c error_function.c parse_input.c init_data.c \
			monitor.c utils.c routine.c destroy.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)
		@echo "To lanch:\n\t./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep>\
 [number_of_times_each_philosopher_must_eat]"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@echo "The objects have been deleted"

fclean : clean
		@rm -f $(NAME)
		@echo "All clean"

re : fclean all

.PHONY: all clean fclean re