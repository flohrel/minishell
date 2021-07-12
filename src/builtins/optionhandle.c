#include "builtins.h"

static int	check_flags(char *str, char *opt)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_ischarset(str[i], opt)))
			return (0);
		i++;
	}
	return (1);
}

static int	check_options(char *str, char *opt, char **flags, t_vars *vars)
{
	int		i;
	t_list	*new;
	char	f[1];

	i = 0;
	if (check_flags(str, opt) == 0)
		return (0);
	while (str[i])
	{
		if (ft_ischarset(str[i], *flags))
		{
			i++;
			continue ;
		}
		f[0] = str[i++];
		*flags = ft_strjoin(*flags, f);
		if (!(*flags))
			return (-1);
		new = ft_lstnew((void *)*flags);
		if (!new)
			return (-1);
		ft_lstadd_front(&vars->ptr_list, new);
	}
	return (1);
}

t_opt	nullopt(void)
{
	t_opt	result;

	result.optflag = NULL;
	result.args = NULL;
	return (result);
}

t_opt	optionhandler(char **args, char *opt, t_vars *vars)
{
	t_opt	options;
	int		i;
	int		j;
	int		ret;

	j = 0;
	i = 0;
	options.optflag = "";
	while (args[i] && ft_startwith(args[i], '-'))
	{
		ret = check_options(args[i] + 1, opt, &(options.optflag), vars);
		if (ret < 0)
			clean_exit(vars, errno);
		else if (ret == 0)
			break ;
		i++;
	}
	options.args = lst_alloc(ft_tablen(args + i) + 1, sizeof(char *),
			vars);
	if (!(options.args))
		return (options);
	while (args[i])
		options.args[j++] = args[i++];
	options.args[j] = NULL;
	return (options);
}
