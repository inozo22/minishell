/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:00:04 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/21 13:03:56 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	int i = -1;
	
	while (envp[++i])
		printf("ptr: %p, var: %s\n", envp[i], envp[i]);
	printf("PATH : %s, ptr: %p\n", getenv("PATH"), getenv("PATH"));
	printf("HOME : %s, ptr: %p\n", getenv("HOME"), getenv("PATH"));
	printf("ROOT : %s, ptr: %p\n", getenv("ROOT"), getenv("PATH"));
	return(0);
}
