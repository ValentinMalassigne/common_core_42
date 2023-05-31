# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 11:18:33 by vmalassi          #+#    #+#              #
#    Updated: 2023/05/31 10:03:49 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
LIBFT = libft

CFLAGS = -Wall -Wextra -Werror

SRC_FILES = push_swap \
			input_checker \
			manage_sorting \
			ft_swap \
			ft_push \
			ft_rotate \
			ft_reverse_rotate \

OBJ_DIR = obj/

SRC = $(addsuffix .c, $(SRC_FILES))
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