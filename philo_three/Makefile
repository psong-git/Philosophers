NAME 	= philo_three

SRCS 	= main.c dining.c initialize.c utils.c messages.c translate.c
OBJS 	= $(SRCS:.c=.o)
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) 

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all