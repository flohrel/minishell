#include "builtins.h"

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
