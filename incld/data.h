/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:01:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/30 18:29:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

enum				e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum				e_tktype
{
	TK_WORD,
	TK_QUOTE,
	TK_DQUOTE,
	TK_SPACE,
	TK_ESC,
	TK_PIPE,
	TK_SEMI,
	TK_LESS,
	TK_GREAT,
	TK_DGREAT,
	TK_NL = -1,
};

enum				e_node
{
	NODE_SEQ,
	NODE_PIPE,
	NODE_CMD,
};

typedef struct		s_env		t_env;
typedef struct		s_lexer		t_lexer;
typedef struct		s_parser	t_parser;
typedef struct		s_vars		t_vars;
typedef struct		s_token		t_token;
typedef struct		s_ast		t_ast;
typedef struct		s_param		t_param;
typedef struct		s_dlist		t_dlist;
typedef struct		s_assign	t_assign;

struct				s_dlist
{
	char			*data;
	t_dlist			*next;
	t_dlist			*prev;
};

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

struct				s_param
{
	bool			has_path;
	char			*path;
	t_list			*redir;
	t_list			*arg;
	t_list			*assign;
};

struct				s_ast
{
	int				type;
	t_param			*data;
	t_ast			*left;
	t_ast			*right;
};

typedef struct		s_term
{
	struct termios	original;
	struct termios	current;
}					t_term;

typedef struct			s_env
{
	char			*key;
	char			*value;
	struct s_env		*next;
}				t_env;

typedef struct		s_vars
{
	t_term			termios;
	t_lexer			lexer;
	t_parser		parser;
	t_dlist			*history;
	t_list			*ptr_list;
	t_env			*env;
}					t_vars;

#endif
