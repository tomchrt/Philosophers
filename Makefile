NAME = philosopher

CC = cc

CFLAGS = -g -fsanitize=thread -pthread -Werror -Wextra -Wall

LIB = -pthread

INC = headers/philosopher.h

SRCS =  check_args.c\
                philo.c\

OBJS =	$(SRCS:.c=.o)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) $(LIB) -o $@

all: $(NAME)

clean:
		rm -rf $(OBJS)

fclean:
		rm -rf $(OBJS)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re