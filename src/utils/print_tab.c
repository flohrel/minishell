#include "minishell.h"

void	print_tab(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		ft_putstr_fd(arg[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}
