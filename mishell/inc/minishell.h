/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/06/08 13:47:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * temporary header
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include "libft.h"
# include <stdbool.h>
# include "built.h"
# include "signals.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MYPROMPT "minishell🐚 > "

/**
 * @brief temporary structure until we make main structure 
 */
typedef struct s_temp
{
	char *const	*envp;
	char *const	*argv;
	int			i;
}	t_temp;

int		built_main(t_temp *temp);
void	set_signal_handlers(void);

#endif