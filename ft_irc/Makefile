# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 10:14:02 by acharlot          #+#    #+#              #
#    Updated: 2024/03/20 14:44:18 by cpothin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variable
MAKEFLAGS	+= --silent

NAME		=	ircserv
NAME_CAPS	= 	IRCSERV
INC			=	inc/
HEADER		=	-I inc
SRC_DIR 	=	src/
OBJ_DIR 	=	obj/
DEBUG_DIR   =   debug/
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98
DFLAGS		= 	-g3 -fno-eliminate-unused-debug-types
RM			=	rm -rf
ECHO		=	echo

#Colors
DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

#Files
MAIN_DIR	=	main/
MAIN_FILES	=	ircserv manageServerLoop
UTIL_DIR	=	utils/
UTIL_FILES	=	manageServerUtils utils parsing commandUtils
CLAS_DIR	=	class/
CLAS_FILES	=	Server Client Channel
COMM_DIR	=	commands/
COMM_FILES	=	bot invite join kick mode motd names nick \
				oper part pass ping privmsg quit topic user
MODE_DIR	=	channel_modes/
MODE_FILES	=	inviteOnly key limit operator topic

SRC_MAI_FILE=	$(addprefix $(MAIN_DIR), $(MAIN_FILES))
SRC_UTI_FILE=	$(addprefix $(UTIL_DIR), $(UTIL_FILES))
SRC_CLA_FILE=	$(addprefix $(CLAS_DIR), $(CLAS_FILES))
SRC_COM_FILE=	$(addprefix $(COMM_DIR), $(COMM_FILES))
SRC_MOD_FILE=	$(addprefix $(MODE_DIR), $(MODE_FILES))

MAINSRC		=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_MAI_FILE)))
UTILSRC		=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_UTI_FILE)))
CLASSRC		=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_CLA_FILE)))
COMMSRC		=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_COM_FILE)))
MODESRC		=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_MOD_FILE)))

MAINOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_MAI_FILE)))
UTILOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_UTI_FILE)))
CLASOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLA_FILE)))
COMMOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_COM_FILE)))
MODEOBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_MOD_FILE)))

DBGMAINOBJ	=	$(addprefix $(DEBUG_DIR), $(addsuffix .o, $(SRC_MAI_FILE)))
DBGUTILOBJ	=	$(addprefix $(DEBUG_DIR), $(addsuffix .o, $(SRC_UTI_FILE)))
DBGCLAOBJ	=	$(addprefix $(DEBUG_DIR), $(addsuffix .o, $(SRC_CLA_FILE)))
DBGCOMOBJ	=	$(addprefix $(DEBUG_DIR), $(addsuffix .o, $(SRC_COM_FILE)))
DBGMODOBJ	=	$(addprefix $(DEBUG_DIR), $(addsuffix .o, $(SRC_MOD_FILE)))

OBJF		=	.cache_exists

OBJ 		=	$(MAINOBJ) $(UTILOBJ) $(CLASOBJ) $(COMMOBJ) $(MODEOBJ)

DBGF 		= 	$(DBGUTILOBJ) $(DBGMAINOBJ) $(DBGCLAOBJ) $(DBGCOMOBJ) $(DBGMODOBJ)

#Rules
all:			$(NAME)

$(NAME):		$(OBJ)
					@$(CC) $(CFLAGS) $(OBJ) $(HEADER) -o $(NAME)
					@$(ECHO) "$(YELLOW)[$(NAME_CAPS)]:\t$(ORANGE)[==========]\t$(GREEN) => Success!$(DEF_COLOR)\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(OBJF)
					@$(CC) $(CFLAGS) -c $< -o $@
					@$(ECHO) "\033[1A\033[K$< created"

$(OBJF):		
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(MAIN_DIR)
					@mkdir -p $(OBJ_DIR)$(UTIL_DIR)
					@mkdir -p $(OBJ_DIR)$(CLAS_DIR)
					@mkdir -p $(OBJ_DIR)$(COMM_DIR)
					@mkdir -p $(OBJ_DIR)$(MODE_DIR)
					@touch $(OBJF)

debug: $(DEBUG_DIR) $(DBGF)
					@$(CC) $(CFLAGS) $(DFLAGS) $(DBGF) $(HEADER) -o $(DEBUG_DIR)$(NAME)
					@$(ECHO) "$(RED)[$(NAME_CAPS)]:\tdebug files$(DEF_COLOR)\t$(GREEN) => Success!$(DEF_COLOR)\n"

$(DEBUG_DIR):
					@mkdir -p $(DEBUG_DIR)
					@mkdir -p $(DEBUG_DIR)$(MAIN_DIR)
					@mkdir -p $(DEBUG_DIR)$(UTIL_DIR)
					@mkdir -p $(DEBUG_DIR)$(CLAS_DIR)
					@mkdir -p $(DEBUG_DIR)$(COMM_DIR)
					@mkdir -p $(DEBUG_DIR)$(MODE_DIR)

$(DEBUG_DIR)%.o: $(SRC_DIR)%.cpp $(OBJF)
					@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

help: ## Print help on Makefile.
					@grep '^[^.#]\+:\s\+.*#' Makefile | \
					sed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "$(GRAY)"`\1`printf "$(DEF_COLOR)"`	\3 /" | \
					expand -t8

clean: ## Clean generated files and cache.
					@$(RM) $(OBJ_DIR)
					@$(RM) $(OBJF)
					@$(RM) $(DEBUG_DIR)
					@$(ECHO) "$(BLUE)[$(NAME_CAPS)]:\tobj. files$(DEF_COLOR)\t$(GREEN) => Cleaned!$(DEF_COLOR)\n"

fclean: ## Clean all generated file, including binaries.		
					@make clean
					@$(RM) $(NAME)
					@$(ECHO) "$(CYAN)[$(NAME_CAPS)]:\texe. files$(DEF_COLOR)\t$(GREEN) => Cleaned!$(DEF_COLOR)\n"
					
re: ## Clean and rebuild binary file.
					@make fclean all
					@$(ECHO) "\n$(GREEN)###\tCleaned and rebuilt everything for [$(NAME_CAPS)]!\t###$(DEF_COLOR)\n"

.PHONY:			all clean fclean re help debug
