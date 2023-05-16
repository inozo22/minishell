/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:29:50 by nimai             #+#    #+#             */
/*   Updated: 2023/05/05 11:29:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../inc/parse.h"

void	init_buffer_string(t_parse_buffer *buf, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	buf->cur_pos = 0;
	buf->size = len;
	buf->lex_stat = LEXSTAT_NOMAL;
	ft_strlcpy(buf->buffer, str, len + 1);
	buf->getc = NULL;
	buf->ungetc = NULL;
}

int	do_cmd(char *cmd)
{
	t_parse_buffer	buf;
	t_parse_ast		*cmdline;
	t_token			tok;
	t_parse_ast		*seqcomd;
	size_t			len;

	len = ft_strlen(cmd);
	init_buffer_string(&buf, cmd);//no se porque me da error
	buf.size++;
	buf.buffer[len] = '\n';
	lex_init_token(&tok);
	lex_get_token(&buf, &tok);

}

int	main(int ac, char **av)
{
	init_shell();
	if (ac == 3 && ft_strncmp(av[1], "-c", 3) == 0)
		return (do_cmd(av[2]));

}

/* int main(int ac, char **av)
{
	int		i;
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;
	char	*ptr5;
	t_mem	*mem;

	mem = NULL;
	i = 0;
	(void)ac;
    (void)av;
	mem = mem_init(mem);
	printf("Kaixo!\n");
	i = ft_strlen("KAIXO");
	ptr1 = mem_malloc_log((char)20, __FILE__, __LINE__, mem);
	ptr2 = mem_malloc_log((char)30, __FILE__, __LINE__, mem);
	ptr3 = mem_malloc_log((char)40, __FILE__, __LINE__, mem);
	ptr4 = mem_malloc_log((char)50, __FILE__, __LINE__, mem);
	ptr5 = mem_malloc_log((char)60, __FILE__, __LINE__, mem);
	mem_del_free(ptr1, mem);
	mem_del_free(ptr3, mem);
	mem_del_free(ptr5, mem);
	mem_check(mem);
	return (0);
} */
