/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:01:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 10:53:28 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

enum	e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum	e_tktype
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

enum	e_node
{
	NODE_SEQ,
	NODE_PIPE,
	NODE_CMD,
};

enum	e_io
{
	FD_IN,
	FD_OUT,
};

typedef struct s_env	t_env;
typedef struct s_lexer	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_vars	t_vars;
typedef struct s_token	t_token;
typedef struct s_ast	t_ast;
typedef struct s_param	t_param;
typedef struct s_assign	t_assign;
typedef struct s_term	t_term;
typedef struct s_env	t_env;
typedef struct s_vars	t_vars;
typedef struct s_opt	t_opt;
typedef struct s_cmd	t_cmd;
typedef struct s_hist	t_hist;

struct	s_hist
{
	t_dlist	*lst;
	t_dlist	*cur;
};

struct	s_token
{
	int		type;
	char	*data;
};

struct	s_lexer
{
	int		state;
	char	*buffer;
	int		buf_len;
	t_list	*tk_list;
	char	*cur_char;
};

struct	s_parser
{
	t_list	*prev_tk;
	t_list	*cur_tk;
	t_ast	*exec_tree;
};

struct	s_param
{
	char	*path;
	t_list	*redir;
	t_list	*arg;
	t_list	*assign;
};

struct	s_ast
{
	int		type;
	t_param	*data;
	t_ast	*left;
	t_ast	*right;
};

struct	s_term
{
	struct termios	original;
	struct termios	current;
};

struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
};

struct	s_opt
{
	char	*optflag;
	char	**args;
};

struct	s_cmd
{
	bool	is_builtin;
	char	*full_path;
	char	**arg;
	int		fd[2];
};

struct	s_vars
{
	t_term		termios;
	t_lexer		lexer;
	t_parser	parser;
	t_list		*ptr_list;
	t_hist		history;
	t_env		*env;
	int			exit_status;
};

#endif
