#ifndef DATA_H
# define DATA_H

# include "libft.h"

# define NTOKTYPE	9

enum				e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum				e_tktype
{
	TK_NULL,
	TK_STR,
	TK_PIPE,
	TK_SEMI,
	TK_QUOTE,
	TK_DQUOTE,
	TK_SPACE,
	TK_ESC,
	TK_GREAT,
	TK_DGREAT,
	TK_LESS,
	TK_VAR,
	TOKEN = -1,
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
	int				buf_len;
	int				ntoken;
	t_list			*tokens;
	void			(*token_handle[3])(t_vars *, int);
};

struct				s_vars
{
	t_lexer			lexer;
};

#endif
