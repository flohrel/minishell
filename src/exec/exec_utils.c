#include "minishell.h"

int	env_size(t_env *env)
{
	int	i;

	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_tab(t_env *env, t_vars *vars)
{
	char	**result;
	int	i;

	result = lst_alloc(env_size(env) + 1, sizeof(char *), vars);
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		result[i] = ft_strjoin(env->key, "=");
		if (!result)
			return (NULL);
		add_to_ptrlst(result[i], vars);
		result[i] = ft_strjoin(result[i], env->value);
		if (!result)
			return (NULL);
		add_to_ptrlst(result[i], vars);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

char	**tabjoin(char *str, char **args, t_vars *vars)
{
	char	**result;
	int	i;
	int	j;

	j = 0;
	i = 1;
	result = lst_alloc(ft_tablen(args) + 2, sizeof(char *), vars);
	if (!result)
		return (NULL);
	result[0] = str;
	result[ft_tablen(args) + 1] = NULL;
	while (result[i])
		result[i++] = args[j++];
	return (result);
}
