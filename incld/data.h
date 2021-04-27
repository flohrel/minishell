#ifndef DATA_H
# define DATA_H

# include "libft.h"
# include <termios.h>

enum				e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum				e_tktype
{
	TK_CHAR,
	TK_QUOTE,
	TK_DQUOTE,
	TK_SPACE,
	TK_ESC,
	TK_PIPE,
	TK_SEMI,
	TK_LESS,
	TK_GREAT,
	TK_DGREAT,
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
	t_list			*tokens;
	char			*cur_char;
};

typedef struct		s_term
{
	struct termios	original;
	struct termios	current;
}					t_term;

typedef struct		s_vars
{
	t_term			termios;
	t_lexer			lexer;
}					t_vars;

#endif
