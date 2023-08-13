# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:55:18 by vmalassi          #+#    #+#              #
#    Updated: 2023/06/09 17:49:32 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft
GET_NEXT_LINE = get_next_line
FT_PRINTF = ft_printf

LIBFT_SRC = ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_strlen \
		ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_strlcpy \
		ft_strlcat \
		ft_toupper \
		ft_tolower \
		ft_strchr \
		ft_strrchr \
		ft_strncmp \
		ft_memchr \
		ft_memcmp \
		ft_strnstr \
		ft_atoi \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_striteri \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap \

GET_NEXT_LINE_SRC = get_next_line \
		get_next_line_utils \

FT_PRINTF_SRC = ft_printf \
			print_char \
			print_str \
			print_ptr \
			print_deci \
			print_unsigned \
			print_hex \
			utils \

SOURCES := $(addprefix $(LIBFT)/, $(LIBFT_SRC)) $(addprefix $(GET_NEXT_LINE)/, $(GET_NEXT_LINE_SRC)) $(addprefix $(FT_PRINTF)/, $(FT_PRINTF_SRC))

SRC_DIR = sources/
OBJ_DIR = objects/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCES)))

OBJF = .cache_exists

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -rf objects/

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

$(OBJF):
	mkdir -p $(OBJ_DIR)/$(LIBFT)
	mkdir -p $(OBJ_DIR)/$(GET_NEXT_LINE)
	mkdir -p $(OBJ_DIR)/$(FT_PRINTF)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	cc $(CFLAGS) -I. -c $< -o $@
