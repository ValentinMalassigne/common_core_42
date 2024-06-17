##############
#
# Compiler
#
##############
CC	= cc
CFLAGS	= -Wall -Wextra -Werror \
	-I$(INCDIR) \
	-I$(LIBDIR)/$(LIBMLXDIR) \
	-I$(LIBDIR)/$(LIBFTDIR) \
	-g3 \
	-O2
#-fsanitize=address

CLFLAGS	= -lXext -lX11 -lm -lbsd

##############
#
# Project files
#
##############
SRCDIR	= src
OBJDIR	= build
INCDIR	= src

OBJ	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
NAME = miniRT
SRC	= color/color.c \
	maths/vec3.c \
	maths/vec3_1.c \
	maths/vec3_2.c \
	maths/maths.c \
	engine/graphics.c \
	engine/graphics_render.c \
	engine/timer.c \
	engine/inputs.c \
	engine/engine.c \
	main/main.c \
	canvas/canvas.c \
	camera/camera.c \
	camera/camera2.c \
	camera/camera3.c \
	parsing/parsing.c \
	parsing/parsing2.c \
	parsing/list.c \
	parsing/get_next_line.c \
	parsing/get_next_line_utils.c \
	parsing/find_params.c \
	parsing/find_spheres.c \
	parsing/find_planes.c \
	parsing/find_cylinders.c \
	parsing/utils.c \
	parsing/utils2.c \
	objects/distance_funcs.c \
	objects/distance_funcs2.c \
	errors/errors.c \

##############
#
# Libraries
#
##############
LIBDIR	= lib
LIBMLXDIR	= minilibx-linux
LIBMLX	= $(LIBDIR)/$(LIBMLXDIR)/libmlx.a
LIBFTDIR	= libft
LIBFT	= $(LIBDIR)/$(LIBFTDIR)/libft.a

##############
#
# Build
#
##############

.PHONY:	all clean fclean re

all:	$(NAME)

$(NAME): $(OBJ) $(LIBMLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(CLFLAGS)

clean:
	rm -rf $(OBJDIR)
	@make -sC $(LIBDIR)/$(LIBMLXDIR) clean
	@make -sC $(LIBDIR)/$(LIBFTDIR) clean

fclean:	clean
	rm -f $(NAME)
	@make -sC $(LIBDIR)/$(LIBFTDIR) fclean

re:	fclean all

#
# project srcs build
#
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

#
# libs build
#
$(LIBMLX):
	@make -sC $(LIBDIR)/$(LIBMLXDIR)

$(LIBFT):
	@make -sC $(LIBDIR)/$(LIBFTDIR)
