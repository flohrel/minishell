int	ft_tablen(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}
