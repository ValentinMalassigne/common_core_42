# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 11:03:52 by vmalassi          #+#    #+#              #
#    Updated: 2024/04/01 11:44:57 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output
NAME	= libft.a

# Includes
INC_DIR	= .

# Sources
SRC_DIR	= src
SRC_	= stdlib/ft_realloc.c \
		   stdlib/ft_atoi.c \
		   stdlib/ft_atol.c \
		   stdlib/ft_atof.c \
		   stdlib/ft_itoa.c \
		   string/ft_bzero.c \
		   string/ft_memcpy.c \
		   string/ft_memset.c \
		   string/ft_strdup.c \
		   string/ft_strlen.c \
		   string/ft_strcmp.c \
		   string/ft_strncmp.c \
		   string/ft_strtok.c \
		   string/ft_strrev.c \
		   ctype/ft_isalnum.c \
		   ctype/ft_isalpha.c \
		   ctype/ft_isdigit.c \
		   ctype/ft_isspace.c \
		   arena/arena.c \
		   arena/arena_alloc.c \
		   list/ft_lstsize.c \

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_))

# Objects
OBJ_DIR		= build
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_:.c=.o))

# Compiler
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I $(INC_DIR) -O3

# Archive
AR			= ar rcs

# Targets
$(NAME):	$(OBJ)
		$(AR) $@ $^
		ranlib $@

all:	$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -rf $(OBJ_DIR)

fclean:	clean
		rm -f $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
