/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmem_check.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:17:26 by nimai             #+#    #+#             */
/*   Updated: 2023/05/10 11:39:34 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMEM_CHECK_H
# define FTMEM_CHECK_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define MAX_MEM 500

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

t_mem	*ftmem_init(t_mem *mem);
void	*ftmem_malloc_log(size_t size, const char *file, unsigned int line, t_mem *mem);
void	ftmem_del_free(void *ptr, t_mem *mem);
void	ftmem_check(t_mem *mem);


#endif
