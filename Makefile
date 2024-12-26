NAME = philo

INC = ./inc/

CC = gcc

CFLAG = -Wall -Wextra -Werror -I -fsanitize=thread

all: $(NAME)

SRC_DIR = src/

OBJ_DIR = obj/

SRCS = philo.c error_function.c parse_input.c init_data.c \
			monitor.c utils.c routine.c destroy.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OB)

fclean :
		rm -rf $(NAME)

re : fclean $(NAME)