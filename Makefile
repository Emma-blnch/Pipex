# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:40:31 by eblancha          #+#    #+#              #
#    Updated: 2024/12/09 12:22:48 by eblancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/ft_pipex.c srcs/ft_pipex_utils.c srcs/ft_create_pipe.c libft/libft.a

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(@)

all: $(NAME)

$(NAME): 
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft

clean_test:
	rm -f outfile infile

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
