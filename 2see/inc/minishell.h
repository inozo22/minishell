/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 12:26:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include "libft.h"
# include "mem_check.h"
# include <stdbool.h>
# include "parse.h"
# include "env.h"
# include "lexer.h"
# include "execution.h"
# include "path.h"
# include "builtin.h"
# include "util.h"

/* typedef struct s_var
{
	const char		*key;
	const char		*value;
	bool			is_shell_var;
	struct s_var	*next;	
}	t_var;
 */

typedef struct s_shell
{
	char	*cwd;
	t_var	*vars;
	int		status;
	int		s_child_received;
	int		heredoc_block;
}	t_shell;
extern	t_shell	g_shell;

/**
 * This struct is used in process
 * that convert AST string node to exec_and_args (array of string).
 */
typedef struct s_cmd_str_node
{
	char			*text;
	t_token_type	type;
}	t_cmd_str_node;


//init_shell.c
int						init_shell(void);
void					init_g_shell(void);

//minish_error.c
/**
 * @brief put error message and exit from the function.
 * @return doesn't return nothing.
 */
void					minish_error_exit(int status, const char *cmd, const char *msg);
void					minish_error(const char *cmd, const char *msg);
int						invoke_sequential_commands(t_parse_ast *seqcmd);
void					die(void);
t_command_invocation	*cmd_ast_pipcmds2cmdinvo(t_parse_node_pipcmds *pipcmds);
t_command_invocation	*cmd_ast_cmd2cmdinvo(t_parse_node_command *cmd);
char					**expand_str_node(t_parse_node_string *str, bool is_ex_cmd);


/* t_command_invocation	*cmd_ast_pipcmds2cmdinvo(t_parse_node_pipcmds *pipcmds);
t_command_invocation	*cmd_ast_cmd2cmdinvo(t_parse_node_command *cmd_node);
char					*string_node2string(t_parse_node_string *string_node,
							bool add_quotes);
char					**expand_string_node(t_parse_node_string *string_node,
							bool is_export_cmd);
char					**split_expanded_str(char *str);
void					set_shell_sighandlers(void);
void					set_sighandlers_during_execution(void);
void					set_sighandlers(t_sighandler sighandler);
void					put_minish_err_msg(const char *cmd_name,
							const char *msg);
int						put_minish_err_msg_and_ret(int ret_val,
							const char *cmd_name, const char *msg);
void					put_minish_err_msg_and_exit(int status,
							const char *cmd_name, const char *msg);
void					check_malloc_has_succeeded(char *cmd_name, void *ptr);
int						invoke_sequential_commands(t_parse_ast *seqcmd);
int						interactive_shell(void);

// Shell initialization
void					init_g_shell(void);
int						initialize_shell(void); */


#endif