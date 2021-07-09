#include "minishell.h"

int	ft_strischarset(char *str, char *set)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		ret = ft_ischarset(str[i], set);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}

int	ft_ischarset(char c, char *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}
