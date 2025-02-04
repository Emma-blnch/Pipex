# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:40:31 by eblancha          #+#    #+#              #
#    Updated: 2025/02/04 09:55:46 by eblancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

MAKEFLAGS += --no-print-directory

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ft_pipex.c ft_pipex_utils.c ft_create_pipe.c ft_errors.c ft_handle_heredoc.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lm -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

clean_test:
	rm -f outfile infile empty

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
