#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int	i;
	int	pid;
	int	ret;
	int	status;

	i = 0;
	if (ac <= 1)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		ret = execve(av[0], av + 1, env);
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("%d\n", pid);
	}
}
