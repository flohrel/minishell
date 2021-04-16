#include <unistd.h>

int	echo(int fd, char **tab, int opt)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			write(fd, &(tab[i][j++]), 1);
		write(fd, " ", 1);
		i++;
	}
	if (opt)
		write(fd, "\n", 1);
	return (1);
}
