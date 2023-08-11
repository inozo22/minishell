# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 19:14:40 by bde-mada          #+#    #+#              #
#    Updated: 2023/08/11 11:29:42 by nimai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isdigit.c ft_isprint.c ft_itoa.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c ft_strndup.c

SRC += get_next_line_bonus.c get_next_line_utils_bonus.c

SRC += ft_atof.c ft_pow.c ft_strcmp.c ft_isspace.c ft_abs.c \
		ft_strcpy.c ft_strcat.c ft_strjoin_many.c ft_lstadd_next_bonus.c

SRCBONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
	ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \

#INCLUDE = libft.h

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEBUG= -g3 -fsanitize=address

PRINTF_DIR	= ft_printf/
PRINTF_LIB	= libftprintf.a
PRINTF	= $(addprefix $(PRINTF_DIR), $(PRINTF_LIB))

OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)

RM = rm -f

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

no_bonus: $(OBJ) $(INCLUDE)
	@ar rcs $(NAME) $(OBJ)
	@echo ✅ "\033[92;3;4mlibft created\033[0m" ✅

$(NAME): $(OBJBONUS) $(OBJ)
	@make -sC $(PRINTF_DIR)
	@echo ✅ "\033[92;3;4mft_printf created\033[0m" ✅
	@mv $(PRINTF) $(NAME)
	@ar rcs $(NAME) $(OBJBONUS) $(OBJ)
	@echo ✅ "\033[92;3;4mlibft created\033[0m" ✅

clean:
	@$(RM) $(OBJ) $(OBJBONUS)
	@make clean -sC $(PRINTF_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
