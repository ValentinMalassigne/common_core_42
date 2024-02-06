NAME = Mon_premier_canon

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_FILES = main\
			Fixed

OBJ_DIR = objects

SRCS = $(addsuffix .cpp, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	c++ $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)