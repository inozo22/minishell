/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:16:58 by nimai             #+#    #+#             */
/*   Updated: 2023/05/22 12:25:23 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_cmd_str_node	**ast_str2cmd_str(t_parse_node_string *str)
{
	t_cmd_str_node	**ret;
	char			*expanded;

	ret = NULL;
	while (str)
	{
		if (str->type == TOKTYPE_NON_EXPANDABLE)
			expanded = ft_strdup(str->text);
		else
			expanded = expand_env_var(str->text);
		/* kokomade */
	}
}


char	**expand_str_node(t_parse_node_string *str, bool is_ex_cmd)
{
	t_cmd_str_node 	**cmd;
	int				i;
	char			**ret;

	cmd = ast_str2cmd_str(str);
	/* kokomade */ 


}
