/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:01:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/07 18:53:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

# define BUFFER_SIZE		65536
# define PROMPT1			"\e[1;32mminishell> \e[0m"
# define PROMPT2			"\e[1;32mminishell\e[0m\e[1;31m> \e[0m"
# define HDOC_PROMPT		"> "

enum	e_state
{
	ST_GENERAL,
	ST_QUOTE,
	ST_DQUOTE,
};

enum	e_tktype
{
	TK_NL = 0x0,
	TK_SPACE = 0x01,
	TK_WORD = 0x02,
	TK_AMP = 0x04,
	TK_PIPE = 0x08,
	TK_REDIR = 0x10000,
	TK_LESS = 0x10100,
	TK_GREAT = 0x10200,
	TK_DLESS = 0x10400,
	TK_DLESS2 = 0x10800,
	TK_DGREAT = 0x11000,
	TK_ESC = 0x20000,
	TK_QUOTE = 0x20010,
	TK_DQUOTE = 0x20020,
	TK_COMPND = 0x40000,
	TK_OPPAR = 0x40040,
	TK_CLPAR = 0x40080,
	TK_LIST = 0x80000,
	TK_DAMP = 0x80004,
	TK_DPIPE = 0x80008,
};

enum	e_node
{
	NODE_SEQ = 0x01,
	NODE_PIPE = 0x02,
	NODE_CMD = 0x04,
	NODE_OR = 0x08,
	NODE_AND = 0x10,
	NODE_LIST = 0x10000,
	NODE_SUB = 0x20000,
};

enum	e_io
{
	RD_IN = 1,
	RD_OUT = 2,
	PIPE_IN = 16,
	PIPE_OUT = 32,
};

enum	e_fd
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
typedef struct s_pipes	t_pipes;

struct	s_token
{
	int		type;
	char	*data;
};

struct	s_lexer
{
	int		esc_st;
	char	*buffer;
	int		buf_len;
	t_list	*tk_list;
	char	*cur_char;
};

struct	s_parser
{
	t_list	*prev_tk;
	t_list	*cur_tk;
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
	int		io_bit;
	char	*delim;
	int		std_out;
	int		std_in;
	int		dup_in;
	int		dup_out;
	int		redir[2];
	int		pipe[2];
};

struct	s_pipes
{
	int				p_open;
	t_ast			*node;
	struct s_pipes	*prev;
	struct s_pipes	*next;
};

struct	s_vars
{
	t_lexer		lexer;
	t_parser	parser;
	t_ast		*exec_tree;
	t_cmd		cmd;
	t_list		*ptr_list;
	t_env		*env;
	t_env		*exp;
	t_env		*agn;
	t_pipes		*pipes;
	int			akuma;
};

extern int			exit_status;

#endif
