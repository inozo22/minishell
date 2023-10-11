/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:25:44 by nimai             #+#    #+#             */
/*   Updated: 2023/10/11 15:50:39 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @note 231010nimai: to swap the list to sort
 */
void	swap_list(t_list **list, t_list *head)
{
	char	*tmp;

	tmp = list[0]->content;
	list[0]->content = list[0]->next->content;
	list[0]->next->content = tmp;
	*list = head;
}

/**
 * @note 231010nimai: to check the length and decide until where I should compare
 */
int	check_variable_len(int len1, int len2)
{
	int	ret;

	ret = 0;
	if (len1 && len2 < 0)
		ret = len1;
	else if (len1 < 0 && len2)
		ret = len2;
	else if (len1 && len2)
	{
		if (len1 > len2)
			ret = len1;
		else
			ret = len2;
	}
	else
		ret = -1;
	return (ret);
}

/**
 * 
 * @param flag if there is no '=', you will put one more length to
 * allocate memory
 */
char	*envp_str_mod(char *str, char *input, int i, int flag)
{
	free (str);
	str = ft_calloc(ft_strlen(input) + 1 + flag, sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, input, i + 2);
	ft_strcat(str, (input + i + 1));
	return (str);
}

int	check_input(char *input, char **env)
{
	int	c;
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		c = 0;
		j = -1;
		while (env[i][++j] == input[c] && input[c] != '=' \
		&& input[c] != '\0' && env[i][j])
			c++;
		if ((input[c] == '=' && env[i][j] == '\0') || (env[i][j] \
		== '=' && input[c] == '\0') || (env[i][j] == input[c]))
			return (c);
		i++;
	}
	return (0);
}
