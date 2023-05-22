/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cmd_invocation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:33:48 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 11:21:32 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_invocation	*cmd_init_cmdinvo(const char **exec_and_args)
{
	t_command_invocation	*cmdinvo;

	cmdinvo = malloc(sizeof(t_command_invocation));
	if (!cmdinvo)
		return (NULL);//free check
	cmdinvo->exec_and_args = exec_and_args;
	cmdinvo->input_redirections = NULL;
	cmdinvo->output_redirections = NULL;
	cmdinvo->piped_cmd = NULL;
	cmdinvo->pid = 0;
	return (cmdinvo);
}
