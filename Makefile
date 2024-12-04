# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:40:31 by eblancha          #+#    #+#              #
#    Updated: 2024/12/04 17:26:58 by eblancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INC)

SRCS = ft_pipex.c ft_pipex_utils.c ft_split.c ft_create_pipe.c

INC = ft_pipex.h

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(@)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

clean_test:
	rm -f outfile infile

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
