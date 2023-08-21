/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:10:38 by bde-mada          #+#    #+#             */
/*   Updated: 2023/08/21 10:52:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>//it's not necessary in POSIX.1
# include <termios.h>
# include "libft.h"
# include "built.h"
# include "signals.h"
//# include "../lib/libft/libft.h"

//test
extern int	g_return_val;

//  enum e_token
// {
// 	WORD = -1,
// 	IS_SPACE = 32,
// 	NEW_LINE = 10,
// 	QOUTE = 39,
// 	DOUBLE_QUOTE = 34,
// 	ESCAPE = 92,
// 	ENV = 36,
// 	PIPE_LINE = 124,
// 	REDIR_IN = 60,
// 	REDIR_OUT = 62,
// 	HERE_DOC,//63
// 	APPEND,//64
// 	INVALID,//65
// };
 enum e_token
{
	WORD = -1,
	IS_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	APPEND,
	INVALID,
};
/*
enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}; */

# define READ_END 0
# define WRITE_END 1

# define SHELL_NAME "nimishell"

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

//"\001" and "\002" are escape sequence, which is necessary to work with readline 
# define COLOR_RESET	"\001\033[0m\002"
# define COLOR_GREEN	"\001\033[1;32m\002"
# define COLOR_YELLOW	"\001\033[1;33m\002"
# define COLOR_GRAY		"\001\033[2;37m\002"
# define COLOR_CURSIVE	"\001\033[3m\002"
# define COLOR_RED		"\001\x1b[31m\002"
# define COLOR_BLUE		"\001\033[1;34m\002"
# define COLOR_CYAN 	"\001\033[1;36m\002"
# define COLOR_ACCENT	"\001\033[92;3;4;1m\002"

//Functions

// minishell_init
void	set_path_list(t_data *data);
char	*get_shlvl(const char *envp);
pid_t	get_my_pid(void);
//static int	fill_env(t_data *data, char *envp[]);

//	minishell

int		minishell(t_data *data);
int		check_builtin(char **input, t_data *data);

//	Lexer

int		lexer(char *input, t_list **token_list);

//	Parser

t_list	*parser(char *str);
char	*remove_quotes(char *str);

//	Terminate
int		errors(int error_id, t_data *data);
void	free_alloc(t_data *data);
void	*free_list(char **list);

//	Error messages
int		error_file(char *prog_name, char *in_file);
int		error_msg(char *prog_name, char *cmd, int mode);

//	Executor
//int child_creation(t_data *data, char **cmd);
int		child_creation(char *infile, char *outfile, t_list *lst, int cmd_number, char **path, char **env, t_data *data);


//	Split
char	**split_input(char *str);

//	Utils
int		ft_isquote(int c);
void	*del(void **ptr);
void	*del_array(void ***ptr);
void	*del_err_array(char ***ptr, int i);

//Bultin
//	errors
void	heap_error(int flag);
//void	error_built(char *cmd, char *av, char *comment);

//	cd
char	*path_modify(char *cur, char *str);

//	echo
int		av_amount(char **strs);

//Expanser
//char	*expanser(char *arg, char *envp[], t_data *data);
char	*expanser(t_list *list, t_data *data);

#endif
