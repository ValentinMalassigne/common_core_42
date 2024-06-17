NAME = Easy_find

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_FILES = main\

OBJ_DIR = objects
SRC_DIR = sources
HPP_DIR = headers

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .cpp, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
HPPS = $(addprefix $(HPP_DIR)/, $(addsuffix .hpp, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	c++ $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)