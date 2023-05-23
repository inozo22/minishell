/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ast2cmdinvo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:26:18 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 18:30:01 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_process_str_node(t_parse_node_string *str, t_command_invocation *cmd)
{
	char		**env;
	const char	**strs;

	if (cmd->exec_and_args && cmd->exec_and_args[0] && != ft_strcmp(cmd->exec_and_args[0], "export"))
		env = expand_str_node(str, true);
}


int	cmd_process_args_node(t_parse_node_arguments *args, t_command_invocation *cmd)
{
	if (args->string_node)
		return (cmd_process_str_node(args->string_node->content.string, cmd));
	else if (args->redirection_node)
		return (cmd_process_redi_node(args->redirection_node->content.redirection, cmd));
	else
		return (1);
}


t_command_invocation	*cmd_ast_cmd2cmdinvo(t_parse_node_command *cmd)
{
	t_command_invocation	*cmdinvo;
	t_parse_node_arguments	*args;

	cmdinvo = cmd_init_cmdinvo(NULL);
	check_malloc("ast2cmdinvo", cmdinvo);
	args = cmd->arguments_node->content.arguments;
	while (args)
	{
		if (cmd_process_args_node(args, cmdinvo))
		{
			cmd_free_cmdinvo(cmdinvo);
			return (NULL);
		}
	}
}


t_command_invocation	*cmd_ast_pipcmds2cmdinvo(t_parse_node_pipcmds *pipcmds)
{
	t_command_invocation	*cmd;
	t_command_invocation	*bandle;

	bandle = NULL;
	while (pipcmds)
	{
		cmd = cmd_ast_cmd2cmdinvo(pipcmds->command_node->content.command);
		if (!cmd)
		{
			cmd_free_cmdinvo(bandle);
		}
	}
}
