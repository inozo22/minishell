/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:05:37 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/22 14:36:39 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int	main()
{
	int 	fd_in;
	int		fd_dup_out;
	int		out_nb;
	int		*out_index;
	char	*buff;
	
	out_nb = -1;
	out_index = (int *)malloc(3 * sizeof(int));
	fd_in = open("../test3", O_RDONLY);
	buff = calloc(1001, sizeof(char));
	read(fd_in, buff, 1000);
	printf("Hey\n");
	if ((out_index[0] = open("../test4", O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		printf("error opening file 4");
	if ((out_index[1] = open("../test5", O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		printf("error opening file 4");
	
	while(++out_nb < 2)
	{
		fd_dup_out = dup(1);
		dup2(out_index[out_nb], 1);
	}
	write(1, buff, strlen(buff));
}