# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 16:02:50 by psong             #+#    #+#              #
#    Updated: 2022/01/04 16:02:54 by psong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

SRCS 	= main.c dining.c initialize.c utils.c utils1.c messages.c
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
