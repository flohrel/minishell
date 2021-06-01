#include "minishell.h"

int	ft_endwith(char *str, char c)
{
	if (str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}
