#ifndef EXIT_H
# define EXIT_H

# include "data.h"
# include "stdlib.h"
# include "stdio.h"
# include "string.h"
# include "errno.h"

void	del_token(void *token);
void	clean_exit(t_vars *vars, int status);

#endif
