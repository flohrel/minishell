#include <parser.h>

void	aff_tab(char **tb)
{
	int	i;

	i = 0;
	while(tb[i])
	{
		ft_putstr_fd(tb[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}

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
	if (str[i - 1] == '*')
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
	if (!(file_name[j]))
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

char	**find_matches(DIR *dir, char *str, t_vars *vars)
{
	struct dirent	*block;
	char		**res;
	char		*match;

	res = NULL;
	do
	{
		block = readdir(dir);
		if (block && block->d_name[0] != '.' &&
				find_match(block->d_name, str))
		{
			match = ft_strdup(block->d_name);
			add_to_ptrlst((void *)match, vars);
			res = tabjoin(match, res, vars);
		}
	}
	while (block);
	return (res);
}

char	**wildcard(char *str, t_vars *vars)
{
	DIR		*cur_dir;
	char		**res;

	if (open_curdir(&cur_dir) < 0)
		return (NULL);
	res = find_matches(cur_dir, str, vars);
	free(cur_dir);
	return (res);
}

int	wctest(char *str, t_vars *vars)
{
	char	**res;

	res = wildcard(str, vars);
	if (!res)
	{
		errormsg("minishell: no matches found:", str);
		return (0);
	}
	aff_tab(res);
	return (1);
}
