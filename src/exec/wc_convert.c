#include "exec.h"

char	**replace_arg(char **args, char **matches, int index, t_vars *vars)
{
	char	**res;
	int		i;

	if (!matches)
		return (args);
	res = malloc(sizeof(char *) * (ft_tablen(args) + ft_tablen(matches)));
	if (!res)
		return (NULL);
	if (!add_to_ptrlst((void *)res, vars))
		return (NULL);
	i = 0;
	while (i < index)
		res[i++] = *(args++);
	args++;
	while (*matches)
		res[i++] = *(matches++);
	while (*args)
		res[i++] = *(args++);
	res[i] = NULL;
	return (res);
}

char	**wildcard_convert(char **args, t_vars *vars)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (args[i])
	{
		if (ft_strischarset(args[i], "*"))
		{
			if (!res)
				res = args;
			res = replace_arg(res, wildcard(args[i], vars),
					i + ft_tablen(res) - ft_tablen(args), vars);
			if (!res)
				return (NULL);
		}
		i++;
	}
	if (!res)
		res = args;
	return (res);
}
