# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 06:17:10 by vmalassi          #+#    #+#              #
#    Updated: 2023/09/06 18:16:12 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft

CFLAGS = -Wall -Wextra -Werror

SRC_DIR := sources
BONUS_DIR := bonus_sources

SRC_FILES = pipex \
			input_parsing \
			utils \

BONUS_FILES = pipex_bonus \
			input_parsing_bonus \
			utils_bonus \

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(addsuffix .c, $(BONUS_FILES)))

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	cc $(CFLAGS) $(SRCS) -o $(NAME) -Llibft -lft

bonus:
	make -C $(LIBFT)
	cc $(CFLAGS) $(BONUS_SRCS) -o $(NAME) -Llibft -lft

clean:
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean $(NAME)
