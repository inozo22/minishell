/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypipe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:05:56 by nimai             #+#    #+#             */
/*   Updated: 2023/05/11 19:02:32 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYPIPE_H
# define MYPIPE_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include "libft.h"
# include "mem_check.h"

# define MAX_MEM 500
# define MAX_CMD 15

typedef struct s_mem_log
{
	void			*ptr;
	size_t			size;
	const char		*file;
	unsigned int	line;
}	t_mem_log;

typedef struct s_mem
{
	int			i;
	t_mem_log	log[MAX_MEM];
}	t_mem;

typedef struct s_cmd
{
	char	*main[10];
	char	*flag[10];

}	t_cmd;

typedef struct s_pine
{
	int		mark;
	t_mem	*mem;
	t_cmd	cmd[MAX_CMD];

}	t_pine;

#endif