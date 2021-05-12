#ifndef DATA_H
# define DATA_H

# include <unistd.h>
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

enum				e_node
{
	NODE_SEQ = 1,
	NODE_PIPE = 2,
	NODE_RDIN = 4,
	NODE_RDAPP = 8
	NODE_RDOUT = 16,
	NODE_CMD = 32,
	NODE_ARG = 64,
	NODE_DATA = 128,
};

typedef struct		s_lexer		t_lexer;
typedef struct		s_parser	t_parser;
typedef struct		s_vars		t_vars;
typedef struct		s_token		t_token;
typedef struct		s_ast		t_ast;

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
	t_list			*tk_list;
	char			*cur_char;
};

struct				s_parser
{
	t_list			*prev_tk;
	t_list			*cur_tk;
	t_ast			*exec_tree;
};

struct				s_ast
{
	int				type;
	char			*data;
	t_ast			*left;
	t_ast			*right;
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
	t_parser		parser;
}					t_vars;

#endif
