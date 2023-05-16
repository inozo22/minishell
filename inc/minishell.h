/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/05/15 11:28:25 by nimai            ###   ########.fr       */
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

typedef struct s_var
{
	const char		*key;
	const char		*value;
	bool			is_shell_var;
	struct s_var	*next;	
}	t_var;


typedef struct s_shell
{
	char	*cwd;
	t_var	*vars;
	int		status;
	int		s_child_received;
	int		heredoc_block;
}	t_shell;
extern	t_shell	g_shell;

#endif