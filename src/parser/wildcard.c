/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:13:58 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/09 17:23:44 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	open_curdir(DIR **cur_dir)
{
	char	cur_pwd[255];

	getcwd(cur_pwd, 255);
	*cur_dir = opendir(cur_pwd);
	if (!*cur_dir)
		return (-1);
	return (1);
}

int	search_match(char *file_name, char *str, int i, int j)
{
	while (str && str[i] == '*')
		i++;
	if (!(str[i]))
		return (1);
	if (i > 0 && str[i - 1] == '*')
	{
		while (str[i] && file_name[j] && file_name[j] != str[i])
			j++;
		if (!(file_name[j]))
			return (0);
	}
	while (file_name[j] && file_name[j] == str[i])
	{
		j++;
		if (str[i + 1])
			i++;
	}
	if (!(file_name[j]) && file_name[j - 1] == str[i])
		return (1);
	else if (str[i] == '*')
		return (search_match(file_name, str, i, j));
	else
		return (0);
}

char	*find_match(char *file_name, char *str)
{
	if (search_match(file_name, str, 0, 0))
		return (file_name);
	else
		return (NULL);
}

char	**find_matches(t_vars *vars, DIR *dir, char *str)
{
	struct dirent	*block;
	char			**res;
	char			*match;
	int				count;

	count = 1;
	res = NULL;
	block = NULL;
	while (block || count)
	{
		count = 0;
		block = readdir(dir);
		if (block && block->d_name[0] != '.'
			&& find_match(block->d_name, str))
		{
			match = ft_strdup(block->d_name);
			add_to_ptrlst((void *)match, vars);
			res = tabjoin(match, res, vars);
		}
	}
	return (res);
}

void	*wildcard(t_vars *vars, char *buffer, char *str)
{
	DIR		*cur_dir;
	char	**strs;
	char	*res;
	char	*match;

	if (open_curdir(&cur_dir) < 0)
		return (NULL);
	match = clear_quotes(str);
	strs = find_matches(vars, cur_dir, match);
	closedir(cur_dir);
	if (!strs)
	{
		ft_strlcpy(buffer, str, ft_strlen(str) + 1);
		free(match);
		return (str);
	}
	free(match);
	res = ft_replace(buffer, strs);
	return (res);
}
