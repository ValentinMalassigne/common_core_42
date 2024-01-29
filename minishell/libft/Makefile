# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 16:55:18 by vmalassi          #+#    #+#              #
#    Updated: 2024/01/29 07:59:09 by vmalassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CFLAGS := -Wall -Wextra -Werror

OBJDIR := objects
SRCDIR := sources

LIBFT := libft
GET_NEXT_LINE := get_next_line
FT_PRINTF := ft_printf

LIBFT_SRC := ft_isalpha \
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
		ft_strcmp \
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
		ft_isspace \

GET_NEXT_LINE_SRC := get_next_line \
		get_next_line_utils \

FT_PRINTF_SRC := ft_printf \
			print_char \
			print_str \
			print_ptr \
			print_deci \
			print_unsigned \
			print_hex \
			utils \

OBJS := $(addprefix $(OBJDIR)/$(LIBFT)/, $(addsuffix .o, $(LIBFT_SRC)))
OBJS += $(addprefix $(OBJDIR)/$(GET_NEXT_LINE)/, $(addsuffix .o, $(GET_NEXT_LINE_SRC)))
OBJS += $(addprefix $(OBJDIR)/$(FT_PRINTF)/, $(addsuffix .o, $(FT_PRINTF_SRC)))

all :$(OBJS) $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf objects/

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	cc $(CFLAGS) -I. -c -o $@ $<

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)/$(LIBFT)/
	mkdir -p $(OBJDIR)/$(GET_NEXT_LINE)
	mkdir -p $(OBJDIR)/$(FT_PRINTF)
