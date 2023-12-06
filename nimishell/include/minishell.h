/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:10:38 by bde-mada          #+#    #+#             */
/*   Updated: 2023/12/06 16:41:45 by bde-mada         ###   ########.fr       */
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
	INVALID = -1,
	WORD = 'a',
	IS_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	APPEND,
};

# define READ_END 0
# define WRITE_END 1

# define SH_NAME "nimishell"
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

char	*get_shlvl(const char *envp);
pid_t	get_my_pid(void);
char	*get_prompt(t_data *data);
//static int	fill_env(t_data *data, char *envp[]);

//	minishell

int		minishell(t_data *data);
int		check_builtin(char **input, t_data *data);
int		process_input(char *line_read, t_data *data);

//	Lexer

// int		lexer(char *input, t_list **token_list);
int		lexer(char *input, t_list **token_list, t_data **data);//***//
int		is_quote(char c);

//	Lexer_utils

int		check_valid_input(char *input);
int		check_literal_metacharacter(int c);
int		is_quote(char c);
int		is_metacharacter(char *str);
int		check_quotes_in_string(char *str);

//	Parser

t_list	*parser(char *str);
//char	*remove_quotes(char *str);
//char	*remove_quotes(char *str, int quotes);
//char	*remove_quotes(char *str, char *ret);

//	Terminate

void	free_null(char **str);
void	free_alloc(t_data *data);
void	*free_list(char **list);

//	Error messages

int		errors(int error_id, t_data *data);
int		error_file(char *in_file);
int		error_msg(char *cmd, int mode);
int		command_not_found_handler(char *name, char *cmd);
int		warning_message(int type, int num);//2309114nimai: added

//	Executer

int		executer(t_list *lst, t_data *data);
//char	**fill_current_cmd(t_list *lst, int pos, char **envp, pid_t pid);
char	**fill_current_cmd(t_list *lst, int pos, t_data *data);

//	Executer_utils

int		execute_script_without_shebang(char **cmd, char **env);
int		close_files_if_error(int fd[2], char *file_name);
void	get_exit_status(t_data *data);
char	**set_path_list(t_data *data);
int		get_iofiles_fd(int *fd, t_list *lst, int pos);

// Executer_utils2

int		check_is_directory(char *cmd);
char	*get_cmd_path(char *cmd, char **path, int *return_val);

// fill_cmd

char	**fill_current_cmd(t_list *lst, int pos, t_data *data);

// 	Redir_setup

int		redir_setup(int pos, int cmd_number, t_data *data);

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

//char	*expander(char *str, char *env[], int pid);
char	*expander(char *str, t_data *data, int *flag);
//char	*expand(t_list *list, t_data *data, char *str);

//	expander_utils

int		expanded_len(char *expanded, char *preceding, char *following);
char	*remove_quotes(char *str);
char	**split_quotes(char *str);
char	*arrange_str(char **tab, char *str, int c);

// expand_utils
char	*get_var_value(char *env_var, char *envp[], int len);
// char	*is_expand(char *env_var, int len, char *env[], pid_t pid);
char	*is_expand(char *env_var, int len, t_data *data);//***///
int		compose_expanded(char *expanded, char **str, int start, int end);
int		is_special_expand(char *str, int ret);
int		check_variable_len(char *str, int start, int quotes);

// heredoc

//int		heredoc_read(char *eof, char **envp, pid_t pid);
int	get_heredoc_input(t_list *lst, int pos, t_data *data);

#endif
