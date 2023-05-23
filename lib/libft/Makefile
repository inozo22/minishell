# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 14:48:52 by nimai             #+#    #+#              #
#    Updated: 2023/05/23 14:14:32 by nimai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libft.a

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
## SRC_DIR     source directory
# SRCS        source files
## BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
## CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# AR           command
# ARFLAGS      ar flags

INCS		:= inc

SRC_DIR     := src
SRCS        := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_get_next_line.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

PRINTF_DIR	:= ft_printf
FTPRINTF	:= $(PRINTF_DIR)/ftprintf.a

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I $(INCS)
AR          := ar
ARFLAGS     := -r -c -s
#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# RF		remove folder
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
RF			:= rm -rf
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> library
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS) $(FTPRINTF)
	@mv $(FTPRINTF) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(info CREATED $@)

$(FTPRINTF):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	$(RM) $(OBJS) $(DEPS)
	$(RF) $(BUILD_DIR)

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: all clean fclean re
.SILENT: