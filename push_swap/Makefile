# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 11:18:33 by vmalassi          #+#    #+#              #
#    Updated: 2023/06/09 13:22:11 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
LIBFT = libft

CFLAGS = -Wall -Wextra -Werror

SRC_FILES = push_swap \
			input_checker \
			manage_sort \
			ft_swap \
			ft_push \
			ft_rotate \
			ft_reverse_rotate \
			utils \
			apply_instructions \
			find_value_place \
			get_lowest_rotations \
			manage_init \
			sort_3_nodes_stack \
			utils_for_a_to_b \
			utils_for_b_to_a \

OBJ_DIR = obj/
SRC_DIR = sources/

SRC = $(addprefix $(OBJ_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

INCLUDE = $(LIBFT)/libft.h

OBJF = .cache_exists

all : $(NAME)

$(NAME) : $(OBJ)
	make bonus -C $(LIBFT)
	cc $(CFLAGS) $(OBJ) -o $(NAME) -Llibft -lft

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re : fclean $(NAME)

$(OBJF):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE) | $(OBJF)
	cc $(CFLAGS) -I. -c $< -o $@

.SILENT: