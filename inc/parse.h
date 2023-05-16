/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:15:51 by nimai             #+#    #+#             */
/*   Updated: 2023/05/16 18:18:57 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../inc/lexer.h"

# define PARSE_BUFFER_SIZE 1024

struct			s_parse_buffer;
typedef int		t_lexer_getc(struct s_parse_buffer *buf);
typedef void	t_lexer_ungetc(struct s_parse_buffer *buf);

typedef struct s_parse_buffer
{
	char			buffer[PARSE_BUFFER_SIZE * 100];
	int				size;
	int				cur_pos;
	t_lexer_state	lex_stat;
	t_lexer_getc	*getc;
	t_lexer_ungetc	*ungetc;
	void			*data;
}	t_parse_buffer;

//minishell.c
/**
 * @brief init as empty except lex_stat and buffer.
 * @return noting.
 */
void	init_buffer_string(t_parse_buffer *buf, char *str);


typedef enum e_parse_ast_type
{
	ASTNODE_NONE = 0xc201,
	ASTNODE_STRING,
	ASTNODE_REDIRECTION,
	ASTNODE_ARGUMENTS,
	ASTNODE_COMMAND,
	ASTNODE_PIPED_COMMANDS,
	ASTNODE_DELIMITER,
	ASTNODE_SEQ_COMMANDS,
	ASTNODE_INVALID,
}	t_parse_ast_type;

typedef struct s_parse_ast t_parse_ast;


typedef struct	s_parse_node_string
{
	char	*text;
	t_token_type	type;
	t_parse_ast		*next;
}	t_parse_node_string;

typedef struct s_parse_node_pipcmds
{
	t_parse_ast	*command_node;
	t_parse_ast	*next;
}	t_parse_node_pipcmds;

typedef struct s_parse_node_command
{
	t_parse_ast	*arguments_node;
}	t_parse_node_command;

typedef struct s_parse_node_arguments
{
	t_parse_ast	*string_node;
	t_parse_ast	*redirection_node;
	t_parse_ast	*rest_node;
}	t_parse_node_argumrnts;

typedef struct s_parse_node_redirection
{
	t_parse_ast		*string_node;
	t_token_type	type;
	int				fd;
}	t_parse_node_redirection;

typedef struct s_parse_node_delimiter
{
	t_token_type	type;
}	t_parse_node_delimiter;

typedef struct s_parse_node_seqcmds
{
	t_parse_ast	*pipcmd_node;
	t_parse_ast	*delimiter_node;
	t_parse_ast	*rest_node;
}	t_parse_node_seqcmds;

typedef struct s_parse_node_cmdline
{
	t_parse_ast	*seqcmd_node;
}	t_parse_node_cmdline;

typedef struct s_parse_hdoc_list
{
	t_parse_node_redirection	*redirection;
	struct s_parse_hdoc_list	*next;
}	t_parse_hdoc_list;

typedef struct s_parse_ast
{
	t_parse_ast_type	type;
	int					error;
	t_parse_hdoc_list	*heredocs;
	union u_parse_ast_node_content
	{
		void						*void_ptr;
		t_parse_node_redirection	*redirection;
		t_parse_node_string			*string;
		t_parse_node_arguments		*arguments;
		t_parse_node_command		*command;
		t_parse_node_pipcmds		*piped_commands;
		t_parse_node_delimiter		*delimiter;
		t_parse_node_seqcmds		*sequential_commands;
		t_parse_node_cmdline		*command_line;
	}	content;
}	t_parse_ast;

//parse_util.c
/**
 * @brief distinguish between > and <.
 * @return NO TENGO NI IDEA QUE return.
 */
void	parse_die(void);





/* t_parse_ast			*parse_new_ast_node(t_parse_ast_type type, void *content);

t_parse_ast			*parse_redirection(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_string(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_arguments(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_command(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_piped_commands(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_delimiter(t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_sequential_commands(
						t_parse_buffer *buf, t_token *tok);
t_parse_ast			*parse_command_line(t_parse_buffer *buf, t_token *tok);

void				parse_die(void);
void				parse_fatal_error(void);
void				parse_skip_spaces(t_parse_buffer *buf, t_token *tok);
t_parse_hdoc_list	*parse_concat_heredocs(
						t_parse_ast *head, t_parse_ast *tail);
t_parse_hdoc_list	*parse_new_heredocs(t_parse_node_redirection *redirection);
void				parse_free_heredocs(t_parse_hdoc_list *list); */

#endif