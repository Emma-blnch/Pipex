# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblancha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:40:31 by eblancha          #+#    #+#              #
#    Updated: 2024/12/04 11:44:20 by eblancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INC)

SRCS = pipex.c utils.c

INC = pipex.h

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(NAME) -c $< -o $(@)

all: $(NAME)

$(NAME): $(OBJS)
	ar rsc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: clean fclean

.PHONY: all clean fclean re
