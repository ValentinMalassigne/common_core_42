NAME	= fractol
BONUS	= fractol_bonus

CC		= cc
CFLAGS	= -Werror -Wextra -Wall

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			=	-I ./headers/\
				-I ./libft/\
				-I ./minilibx-linux/

SRC_PATH	=	sources/

SRC			=	fractol.c \
				initializations.c \
				utils.c \
				events.c \
				render.c \
				manage_colors.c \
				instructions.c \
				calculate_fractals.c

SRC_BONUS	=	fractol_bonus.c \
				initializations.c \
				utils.c \
				events.c \
				events_bonus.c \
				render.c \
				manage_colors.c \
				instructions.c \
				instructions_bonus.c \
				calculate_fractals.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

SRCS_BONUS	= $(addprefix $(SRC_BONUS), $(SRC_BONUS))

OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_BONUS_PATH	= obj/

OBJ_BONUS	= $(SRC_BONUS:.c=.o)
OBJS_BONUS	= $(addprefix $(OBJ_PATH), $(OBJ_BONUS))

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_BONUS_PATH)%.o: $(SRC_BONUS)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJS_BONUS): $(OBJ_BONUS_PATH)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_BONUS_PATH):
	mkdir $(OBJ_BONUS_PATH)

$(MLX):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm

$(BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm

bonus: $(MLX) $(LIBFT) $(BONUS)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C $(MLX_PATH)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean