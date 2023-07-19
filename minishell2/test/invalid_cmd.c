/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-mada <bde-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:10:48 by bde-mada          #+#    #+#             */
/*   Updated: 2023/06/24 11:19:11 by bde-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	char *args[10] = {"ls", "..", NULL};
	
	execve("/bins/ls", args, env);
	perror("Minishell");
}