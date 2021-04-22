#ifndef DATA_H
# define DATA_H

# include "libft.h"

enum				e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum				e_tktype
{
	TOKEN = -1,
	TK_NULL = 0,
	TK_QUOTE,
	TK_DQUOTE,
	TK_SPACE,
	TK_ESC,
	TK_VAR,
	TK_PIPE,
	TK_SEMI,
	TK_LESS,
	TK_GREAT,
	TK_DGREAT,
};

typedef struct		s_lexer	t_lexer;
typedef struct		s_vars	t_vars;

typedef struct		s_token	t_token;
struct				s_token
{
	int				type;
	char			*data;
};


struct				s_lexer
{
	int				state;
	char			*buffer;
	int				ntoken;
	t_list			*tokens;
	void			(*token_handle[3])(t_vars *, int);
};

struct				s_vars
{
	t_lexer			lexer;
};

#endif
