# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:55:18 by vmalassi          #+#    #+#              #
#    Updated: 2023/05/11 08:06:20 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft

CFLAGS = -Wall -Wextra -Werror

SRC_FILES = ft_printf \
			print_char \
			print_str \
			print_ptr \
			print_deci \
			print_unsigned \
			print_hex \
			utils 

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

INCLUDE = includes/libft.h

OBJF = .cache_exists

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(LIBFT)
	cp libft/libft.a .
	mv libft.a $(NAME)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean $(NAME)

$(OBJF):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE) | $(OBJF)
	cc $(CFLAGS) -I. -c $< -o $@
