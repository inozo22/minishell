/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:10:38 by bde-mada          #+#    #+#             */
/*   Updated: 2023/09/26 19:13:05 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include "libft.h"
# include "built.h"
# include "signals.h"
# include <sys/wait.h>

# ifndef TCSASOFT
#  define TCSASOFT 0
# endif

extern volatile int	g_return_val;

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

# define READ_END 0
# define WRITE_END 1

# define SHELL_NAME "nimishell"
# define DEFAULT_PATH "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin"

typedef struct s_tokens
{
	char			*content;
	int				len;
	struct s_list	*next;
}				t_tokens;

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

//# define SHELL_COLOR_ESCAPE_SEQ(X) "\033["X"m"
//# define SHELL_FORMAT_RESET ANSI_COLOR_ESCAPE_SEQ(GEN_FORMAT_RESET)

//"\001" and "\002" are escape sequence, necessary to work with readline
# define COLOR_RESET	"\001\033[0m\002"
# define COLOR_GREEN	"\001\033[1;32m\002"
# define COLOR_YELLOW	"\001\033[1;33m\002"
# define COLOR_GRAY		"\001\033[2;37m\002"
# define COLOR_CURSIVE	"\001\033[3m\002"
# define COLOR_RED		"\001\033[31m\002"
# define COLOR_BLUE		"\001\033[1;34m\002"
# define COLOR_CYAN 	"\001\033[1;36m\002"
# define COLOR_ACCENT	"\001\033[92;3;4;1m\002"

//FUNCTION PROTOTYPES
// minishell_init

void	set_path_list(t_data *data);
char	*get_shlvl(const char *envp);
pid_t	get_my_pid(void);
char	*get_prompt(t_data *data);
//static int	fill_env(t_data *data, char *envp[]);

//	minishell

int		minishell(t_data *data);
int		check_builtin(char **input, t_data *data);
int		process_input(char *line_read, t_data *data);

//	Lexer

int		lexer(char *input, t_list **token_list);
int		is_quote(char c);

//	Lexer_utils

int		check_valid_input(char *input);
int		check_literal_metacharacter(int c);

//	Parser

t_list	*parser(char *str);
//char	*remove_quotes(char *str);
//char	*remove_quotes(char *str, int quotes);
//char	*remove_quotes(char *str, char *ret);

//	Terminate

int		errors(int error_id, t_data *data);
void	free_alloc(t_data *data);
void	*free_list(char **list);

//	Error messages

int		error_file(char *in_file);
int		error_msg(char *cmd, int mode);
int		command_not_found_handler(char *name, char *cmd);
int		warning_message(int type, int num);//2309114nimai: added

//	Executer

int		executer(t_list *lst, int cmd_number, \
					char **path, char **env, t_data *data);
char	**fill_current_cmd(t_list *lst, int pos, char **envp, pid_t pid);

//	Executer_utils

int		check_is_directory(char *cmd);
char	*get_cmd_path(char *cmd, char **path, int *return_val);
int		execute_script_without_shebang(char **cmd, char **env);
int 	close_files_if_error(int fd[2], char *file_name);
int		check_exit_status(int e_status);

// 	Redir_setup

void	redir_setup(int pos, int cmd_number, int *process_fd, int *pipe_fd, int *tmp_stdio_fd);

//	Split

char	**split_input(char *str);

//	Utils

int		ft_isquote(int c);
void	*del(void **ptr);
void	*del_array(void ***ptr);
void	*del_err_array(char ***ptr, int i);
void	*del_triple_array(char ****ptr);
int		update_last_executed_cmd(t_data *data, char **input);
// int		update_last_executed_cmd(t_data *data, char *cmd);

//Bultin
//	errors

void	heap_error(int flag);
//void	error_built(char *cmd, char *av, char *comment);

//	cd
char	*path_modify(char *cur, char *str);

//	echo
int		av_amount(char **strs);

//Expanser

char	*expander(char *str, char *env[], int pid);
//char	*expand(t_list *list, t_data *data, char *str);

//	expander_utils

int		expanded_len(char *expanded, char *preceding, char *following);
char	*remove_quotes(char *str);
char	**split_quotes(char *str);
char	*arrange_str(char **tab, char *str, int c);

//Redirect

int		heredoc_read(char *eof, char **envp, pid_t pid);

#endif
