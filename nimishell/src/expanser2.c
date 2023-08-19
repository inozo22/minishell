#include "minishell.h"
#include "../lib/libft/libft.h"

int	count_expanded(char *str)
{
	int	ret;

	ret = 0;
	while (ft_isalnum(str[ret]))
		ret++;
	return (ret);
}

char	*expand(t_list *list, t_data *data, char *str)
{
	int	i;

	i = -1;
	(void)list;
	while (data->env[++i])
	{
		if (!ft_strncmp(str + 1, data->env[i], count_expanded(str) - 1) && data->env[i])
			return (ft_strdup(data->env[i] + count_expanded(str)));
	}
	if (!data->env[i])
		return (NULL);
	return (0);
}


char	*obtain_no_expanded(char *str)
{
	char	*ret;
	int		i;
	int		len;
	int		flag;

	printf("Line: %d str: %s\n", __LINE__, str);
	flag = 0;
	i = 0;
	if (str[i] == '\'')
	{
		i++;
		flag++;
	}
	while (ft_isalnum(str[i]))
	{
		i++;
		len++;
	}
	// i = 0;
	// if (str[i] == '\'' || str[i] == '\"')
	// {
	// 	i++;
	// 	len -= 2;
	// }
	ret = ft_calloc(len + 1 - flag, 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, len + 1 - flag);
	printf("Line: %d	ret: %s\n", __LINE__, ret);
	return (ret);
}

// char	*obtain_no_expanded(char *str)
// {
// 	char	*ret;
// 	int		i;
// 	int		len;

// 	len = ft_strlen(str);
// 	i = 0;
// 	if (str[i] == '\'' || str[i] == '\"')
// 	{
// 		i++;
// 		len -= 2;
// 	}
// 	ret = ft_calloc(len, 1);
// 	if (!ret)
// 		return (NULL);
// 	ft_strcpy(ret, str);
// 	printf("Line: %d	ret: %s\n", __LINE__, ret);
// 	return (ret);
// }

char	*expanser(t_list *list, t_data *data)
{
	char	*ret;
	char	*tmp;
	char	*expanded;
	int		i;
//	int		g;

//	(void)data;
	ret = NULL;
	tmp = NULL;
	expanded = NULL;
	i = 0;
	while (list->content[i])
	{
		printf("ret: %s list->content[%d]: %s\n", ret, i, &list->content[i]);
		if (list->content[i] == '\'')//obtain string with single quotes
		{
			expanded = obtain_no_expanded(&list->content[i]);
//			printf("Line: %d	expanded: %s\n", __LINE__, expanded);
			i = i + ft_strlen(expanded) + 2;
		}
		else if (ft_strncmp(&list->content[i], "$?", 2) == 0)
		{
			expanded = ft_itoa(data->return_val);
//			printf("Line: %d	expanded: %s\n", __LINE__, expanded);
			i += 2;
		}
		else if (list->content[i] == '$')
		{
			expanded = expand(list, data, &list->content[i]);
//			printf("Line: %d	expanded: %s\n", __LINE__, expanded);
			i = count_expanded(&list->content[i]);
		}
		else//obtain string not expanded
		{
			expanded = obtain_no_expanded(&list->content[i]);
//			printf("Line: %d	expanded: %s\n", __LINE__, expanded);
			i += ft_strlen(expanded);
		}
//		printf("Line: %d	expanded: %s\n", __LINE__, expanded);
		if (ret)
			printf("Line: %d	ret: %s\n", __LINE__, ret);
		if (!ret)
			ret = expanded;
		else
		{
			tmp = ft_strdup(ret);
			free (ret);
			printf("Line: %d	expanded: %s ret: %s tmp: %s\n", __LINE__, expanded, ret, tmp);
			ret = ft_calloc(ft_strlen(expanded) + ft_strlen(tmp) + 1, 1);
			ret = ft_strjoin(tmp, expanded);
			free (tmp);
		}
		printf("Line: %d	ret: %s, expanded: %s\n", __LINE__, ret, expanded);
	}



	return (ret);
}
