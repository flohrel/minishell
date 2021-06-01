#include "minishell.h"

static char	*check_options(char *str, char *opt, char *flags, t_vars *vars)
{
	int		i;
	char	*result;
	t_list	*new;
	char	f[1];

	i = 0;
	while (str[i])
	{
		if (ft_ischarset(str[i], flags))
		{
			i++;
			continue ;
		}
		if (!(ft_ischarset(str[i], opt)))
			return (NULL);
		f[0] = str[i++];
		result = ft_strjoin(flags, f);
		if (!result)
			return (NULL);
		new = ft_lstnew((void *)result);
		if (!new)
			return (NULL);
		ft_lstadd_front(&vars->ptr_list, new);
	}
	return (result);
}

t_opt	optionhandler(char **args, char *opt, t_vars *vars)
{
	t_opt	options;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (args[i] && ft_startwith(args[i], '-'))
	{
		options.optflag = check_options(args[i++] + 1, opt,
				options.optflag, vars);
	}
	options.args = lst_alloc(ft_tablen(args + i), sizeof(char *),
			vars);
	if (!(options.args))
		return (options);
	while (args[i])
		options.args[j++] = args[i++];
	return (options);
}
