/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:10:38 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/19 14:24:09 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "built.h"
# include "signals.h"

/* enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}; */

//# define SHELL_NAME "minihell🤪"
# define SHELL_NAME "minishell🐚"
# define BUILTIN builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL}

typedef struct s_tokens
{
	char			*content;
	int				len;
	struct s_list	*next;
}				t_tokens;
/* 	enum			e_token;
	enum			e_flag; */

/* typedef struct s_data
{
	char		**env;
	char		**path;
	int			return_val;
//	t_tokens	*head;
}				t_data; */

//General Formatting
# define GEN_FORMAT_RESET                "0"
# define GEN_FORMAT_BRIGHT               "1"
# define GEN_FORMAT_DIM                  "2"
# define GEN_FORMAT_UNDERSCORE           "3"
# define GEN_FORMAT_BLINK                "4"
# define GEN_FORMAT_REVERSE              "5"
# define GEN_FORMAT_HIDDEN               "6"

//Foreground Colors
# define FOREGROUND_COL_BLACK            "30"
# define FOREGROUND_COL_RED              "31"
# define FOREGROUND_COL_GREEN            "32"
# define FOREGROUND_COL_YELLOW           "33"
# define FOREGROUND_COL_BLUE             "34"
# define FOREGROUND_COL_MAGENTA          "35"
# define FOREGROUND_COL_CYAN             "36"
# define FOREGROUND_COL_WHITE            "37"

//Background Colors
# define BACKGROUND_COL_BLACK            "40"
# define BACKGROUND_COL_RED              "41"
# define BACKGROUND_COL_GREEN            "42"
# define BACKGROUND_COL_YELLOW           "43"
# define BACKGROUND_COL_BLUE             "44"
# define BACKGROUND_COL_MAGENTA          "45"
# define BACKGROUND_COL_CYAN             "46"
# define BACKGROUND_COL_WHITE            "47"

# define SHELL_COLOR_ESCAPE_SEQ(X) "\x1b["X"m"
# define SHELL_FORMAT_RESET ANSI_COLOR_ESCAPE_SEQ(GEN_FORMAT_RESET)

# define COLOR_RESET	"\033[0m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_GRAY		"\033[2;37m"
# define COLOR_CURSIVE	"\033[3m"
# define COLOR_RED		"\x1b[31m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_CYAN 	"\033[1;36m"
# define COLOR_ACCENT	"\033[92;3;4;1m"

//Functions
//	minishell
int		minishell(t_data *data);
//	Terminate
void	errors(int error_id, t_data *data);
void	*free_alloc(t_data *data);
void	*free_list(char **list);

//	Error messages
int		error_file(char *prog_name, char *in_file);
void	error_cmdnotfound(char *prog_name, char *cmd);

//	Split
char	**split_input(char *str);

//	Utils
void	*del(void **ptr);
void	*del_array(void ***ptr);
void	*del_err_array(char ***ptr, int i);

//Bultin
//	errors
void	heap_error(int flag);


//	cd
char	*path_modify(char *cur, char *str);

//	echo
int		av_amount(char **strs);

#endif
