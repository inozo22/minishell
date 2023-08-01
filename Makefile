# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 13:14:38 by bde-mada          #+#    #+#              #
#    Updated: 2023/08/01 13:24:18 by nimai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

define ASCIIART

       /^-^\         /^-----^\\
      / o o \        V  o o  V
     /   ▼   \        |  ▽  |
     V \ ∧ / V         \ Q / 
       / - \\           / - \\
      /    | ========= |    \\
(    /     | minishell |     \\     )
 ===/___) || ========= || (___\\====
						
endef
export ASCIIART

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -pedantic

OS			= $(shell uname)

#Optimization and valgrind debugging flags:
DEBUG			:= -g3 -O0 #-fsanitize=address 
#change -O0 with -O1 or -O2 for faster execution but worse info

LDFLAGS		= $(addprefix -L, $(LIBS_DIR))
LDLIBS		= $(addprefix -l, $(LIBS))
INC			= -I$(INC_DIR) -I$(LIBS_DIR)

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= include/

LIBS		:= ft #mlx
INCLUDE		:= minishell.h
SRC_FILES	:=  main.c minishell.c terminate.c error_msgs.c utils.c cmd_split.c \
				redirect.c expanser2.c lexer.c parser.c executor.c\
				builtin/built_cd_path.c builtin/built_cd.c builtin/built_cd_utils.c builtin/built_echo.c \
				builtin/built_env.c builtin/built_exit.c builtin/built_export.c \
				builtin/built_export_output.c builtin/built_utils.c \
				builtin/built_export_sort.c builtin/built_pwd.c builtin/built_unset.c \
				builtin/errors.c builtin/free.c \
				signals.c #wildcards.c 

OBJ_FILES	:= $(SRC_FILES:.c=.o)

LIBS_DIR	:= $(addprefix lib/lib, $(LIBS))
SRCS		:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES	:= $(addprefix $(INC_DIR), $(INCLUDE))


NONE		:= "\033[0m"
GREEN		:= "\033[32m"
YELLOW		:= "\033[1;33m"
GRAY		:= "\033[2;37m"
CURSIVE		:= "\033[3m"
RED			:= "\x1b[31m"
BLUE		:= "\033[1;34m"
CYAN 		:= "\033[1;36m"
ACCENT		:= "\033[92;3;4;1m"

#ifeq ($(OS), Darwin)
#	LNK+= -Imlx -lmlx -framework OpenGL -framework AppKit
#else
#	MLX_DIR = libmlx_linux/
#	LNK+= -lXext -lX11 -lm -lz
#endif

ifeq ($(OS), Darwin)
	LDFLAGS += -L/Users/$(USER)/.brew/opt/readline/lib
	LDLIBS	+= -lreadline
	INC		+= -I/Users/$(USER)/.brew/opt/readline/include
else
	LDLIBS	+= lib/libft/libft.a /lib/x86_64-linux-gnu/libreadline.so
endif

all: $(LIBS) obj $(NAME)
	@echo $(YELLOW)"$$ASCIIART"$(NONE)

obj:
	@echo $(CURSIVE)$(GRAY) "		- Creating object directory..." $(NONE)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtin
	@echo $(CURSIVE)$(GRAY) "		- Making object files..." $(NONE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INC) $(LNK) $(DEBUG) -c $< -o $@

$(NAME): $(OBJS) $(INCLUDES)
	@echo $(CURSIVE)$(GRAY) "		- Compiling project $(NAME)..." $(NONE)
	$(CC) $(CFLAGS) $(INC) $(DEBUG) $(OBJS) $(LDFLAGS) $(LDLIBS) $(LNK) -o $(NAME)
	@echo $(ACCENT)"✅ $(NAME) compiled ✅"$(NONE)

$(LIBS): $(LIBS_DIR)
	@echo $(CURSIVE)$(GRAY) "		- Compiling libs..." $(NONE)
	@make -sC $<

clean: $(LIBS_DIR)
	@make clean -sC $<
	@rm -Rf $(OBJ_DIR)
	@echo $(RED) Objects deleted!$(NONE) 🗑

fclean: $(LIBS_DIR)
	@make fclean -sC $<
	@rm -Rf $(NAME) $(OBJ_DIR)
	@echo $(RED) "Objects & $(NAME) executable deleted!"$(NONE) 🗑❌

norm:
	@norminette src include lib

leak:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

leaks2: $(NAME) all
	$(eval DEBUG += leak -fsanitize=address -static-libasan)
	$(NAME)

re: fclean all

.phony: all clean fclean re norm bonus

# List all the used functions to check if there is a forbidden one:
#objdump -t obj/* | grep "*UND*" | awk '{print $3}' | sort -u