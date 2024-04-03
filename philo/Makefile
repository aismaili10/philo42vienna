# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 12:51:14 by aismaili          #+#    #+#              #
#    Updated: 2024/04/03 13:26:19 by aismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = @/bin/rm -f

SRCS = philo.c utils.c man_input.c prep_create_t.c threads.c clean_up.c

OBJS = $(SRCS:.c=.o)

.PHONY: all re clean fclean debug

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
debug: CFLAGS += -g
debug: re