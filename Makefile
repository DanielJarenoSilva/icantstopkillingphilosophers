# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 13:13:43 by djareno           #+#    #+#              #
#    Updated: 2025/11/12 12:25:54 by djareno          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo

SRCS         = philo.c \
				philo_utils.c \
				philo_actions.c \
				philosophers.c \

OBJS        = $(SRCS:.c=.o)

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -pthread -g3

RM          = rm -f

# Reglas
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re