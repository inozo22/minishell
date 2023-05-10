/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:16:20 by nimai             #+#    #+#             */
/*   Updated: 2023/05/02 16:41:07 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *memo, char *buff)
{
	ssize_t	i;
	ssize_t	c;
	char	*ret;

	if (!memo)
	{
		memo = (char *)malloc(1 * sizeof(char));
		memo[0] = '\0';
	}
	if (!memo || !buff)
		return (NULL);
	ret = malloc(ft_strlen(memo) + ft_strlen(buff) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	c = 0;
	while (memo[++i] != '\0')
		ret[i] = memo[i];
	while (buff[c] != '\0')
		ret[i++] = buff[c++];
	ret[i] = '\0';
	free(memo);
	return (ret);
}

char	*get_ret(char *memo)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!memo[i])
		return (NULL);
	while (memo[i] && memo[i] != '\n')
		i++;
	if (memo[i] == '\n')
		ret = (char *)malloc((i + 2) * sizeof(char));
	else
		ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (memo[i] && memo[i] != '\n')
	{
		ret[i] = memo[i];
		i++;
	}
	if (memo[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*crop_memo(char *memo)
{
	size_t		i;
	size_t		c;
	char		*ret;

	i = 0;
	while (memo[i] && memo[i] != '\n')
		i++;
	if (!memo[i])
	{
		free(memo);
		return (NULL);
	}
	ret = (char *)malloc((ft_strlen(memo) - i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i++;
	c = 0;
	while (memo[i])
		ret[c++] = memo[i++];
	ret[c] = '\0';
	free(memo);
	return (ret);
}

char	*read_memo(int fd, char *memo)
{
	char	*buff;
	ssize_t	ret_read;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	ret_read = 1;
	while (ret_read > 0 && ((!memo) || !ft_strchr(memo, '\n')))
	{
		ret_read = read(fd, buff, BUFFER_SIZE);
		if (ret_read == -1)
		{
			free(buff);
			free(memo);
			return (NULL);
		}
		buff[ret_read] = '\0';
		memo = gnl_strjoin(memo, buff);
	}
	free(buff);
	return (memo);
}

char	*ft_get_next_line(int fd)
{
	static char	*memo[1024];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	memo[fd] = read_memo(fd, memo[fd]);
	if (!memo[fd])
		return (NULL);
	ret = get_ret(memo[fd]);
	memo[fd] = crop_memo(memo[fd]);
	return (ret);
}
