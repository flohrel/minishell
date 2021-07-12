#include "builtins.h"

int	ft_already(char *str, int index, char c)
{
	int	i;

	i = 0;
	while (str[i] && i < index)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
