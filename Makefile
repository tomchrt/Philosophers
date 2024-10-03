NAME = philosopher

CC = cc

CFLAGS = -g -fsanitize=thread -pthread -Werror -Wextra -Wall

LIB = -pthread

INC = headers/philosopher.h

SRCS =  main.c\
               checker_init.c\
			   check_args.c\
			   create_philos.c\
			   get_time.c\
			   routine.c\
			   print_utils.c\
			   eating.c\
			   dead_utils.c\

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
