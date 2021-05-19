#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "data.h"
# include "lexer.h"

void	free_vars(t_vars *vars);
void	clean_exit(t_vars *vars, int status);

#endif
