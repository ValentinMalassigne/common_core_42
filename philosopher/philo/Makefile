NAME = philo

CFLAGS = -Wall -Wextra -Werror

LINKED_LIBRARY = -lpthread

SRC_DIR = sources
OBJ_DIR = objects

SRC_FILES = philo \
			utils \
			init \
			manage_threads \
			parsing \
			routine \
			clear \

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(LINKED_LIBRARY) $(OBJS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) -I. -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)