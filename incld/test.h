#ifndef TEST_H
# define TEST_H

# include "libft.h"

typedef struct	s_cmd
{
	const char *cmd_path;
	char *const	argv[];
	char *const	envp[];
}				t_cmd;

#endif
