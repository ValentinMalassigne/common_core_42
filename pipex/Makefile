# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 06:17:10 by vmalassi          #+#    #+#              #
#    Updated: 2023/07/15 08:34:24 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft

CFLAGS = -Wall -Wextra -Werror

SRC_FILES = pipex \

SRC_DIR = sources/
OBJ_DIR = obj/pipex/

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	cc $(CFLAGS) $(OBJ) -o $(NAME) -Llibft -lft

clean:
	rm -rf obj/
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean $(NAME)

$(OBJF):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
	cc $(CFLAGS) -I. -c $< -o $@

.SILENT: