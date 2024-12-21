# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 12:51:14 by aismaili          #+#    #+#              #
#    Updated: 2024/04/05 14:13:38 by aismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = @/bin/rm -f

SRCS =	philo.c utils.c \
		man_input.c prep_create_t.c \
		threads.c clean_up_and_msg.c routine.c \
		ft_eat.c ft_monitor.c

OBJS = $(SRCS:.c=.o)

.PHONY: all re clean fclean debug

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

#%.o: %.c
#	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
debug: CFLAGS += -g #-fsanitize=thread
debug: re