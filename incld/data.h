#ifndef DATA_H
# define DATA_H

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
	TK_SEMCOL,
	TK_QUOTE,
	TK_DQUOTE,
	TK_SPACE,
	TK_ESCAPE,
	TK_RDOUT,
	TK_RDAPP,
	TK_RDIN,
	TOKEN = -1,
};

typedef struct		s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct		s_lexer	t_lexer;
typedef struct		s_vars	t_vars;

struct				s_lexer
{
	int				state;
	char			*buffer;
	int				buf_len;
	int				ntoken;
	t_token			*token_list;
	void			(*token_handle[3])(t_vars *);
};

struct				s_vars
{
	t_lexer			lexer;
};

#endif
