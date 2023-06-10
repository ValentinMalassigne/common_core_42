# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 11:18:33 by vmalassi          #+#    #+#              #
#    Updated: 2023/06/10 14:30:51 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
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

BONUS_SRC_FILES = checker \

SRC_DIR = sources/
OBJ_DIR = obj/push_swap/
BONUS_SRC_DIR = bonus/
BONUS_OBJ_DIR = obj/bonus/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(addsuffix .o, $(BONUS_SRC_FILES)))

OBJF = .cache_exists

all : $(NAME)

$(NAME) : $(OBJ)
	make -C $(LIBFT)
	cc $(CFLAGS) $(OBJ) -o $(NAME) -Llibft -lft

bonus : all $(BONUS_OBJ)
	cc $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME) -Llibft -lft

clean :
	rm -rf obj/
	make clean -C $(LIBFT)

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C $(LIBFT)

re : fclean $(NAME)

$(OBJF):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BONUS_OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
	cc $(CFLAGS) -I. -c $< -o $@

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_OBJF)
	cc $(CFLAGS) -I. -c $< -o $@

.SILENT: