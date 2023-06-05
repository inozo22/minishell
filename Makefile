# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:53:13 by nimai             #+#    #+#              #
#    Updated: 2023/06/05 16:06:53 by nimai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

LIBS		:=  ft #readline history
LIBS_TARGET	:= \
				lib/libft/libft.a \
#				/Users/$(USER)/.brew/opt/readline/lib/libreadline.a \
				/Users/$(USER)/.brew/opt/readline/lib/libhistory.a

INCS		:= \
				inc \
				lib/libft/inc \
#				/Users/$(USER)/.brew/opt/readline/include/

SRC_DIR		:= src
SRCS		:= \
				main.c \
				built_exit.c \
				built_pwd.c \
				built_echo.c \
				built_cd.c \
				built_cd_path.c \
				built_export.c \
				built_export_sort.c \
				built_env.c \
				built_unset.c \
				errors.c \
				free.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
CFLAGS		:= -g3 -Wall -Wextra -Werror
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS_TARGET))) 
LDLIBS		:= $(addprefix -l,$(LIBS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#

RM			:= rm -f
RF			:= rm -rf
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   ASCII ART                                    #
#------------------------------------------------#
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

define	ART
$(YELLOW)
       /^-^\         /^-----^\\
      / o o \        V  o o  V
     /   ▼   \        |  ▽  |
     V \ ∧ / V         \ Q / 
       / - \\           / - \\
      /    | ========= |    \\
(    /     | minishell |     \\     )
 ===/___) || ========= || (___\\====$(CLR_RMV)
endef
export	ART

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))
	@echo "$$ART"

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(MAKE) -C lib/libft clean
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C lib/libft fclean
	$(RM) $(NAME)
	$(RF) ./minishell.dSYM
	$(RF) $(BUILD_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT: