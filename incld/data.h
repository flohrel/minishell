/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:01:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/20 12:48:27 by flohrel          ###   ########.fr       */
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
	ST_GENERAL = 0x01,
	ST_QUOTE = 0x02,
	ST_DQUOTE = 0x04,
	ST_WILD = 0x08,
};

enum	e_tktype
{
	TK_SPACE = 0x01,
	TK_WORD = 0x02,
	TK_AMP = 0x04,
	TK_PIPE = 0x08,
	TK_QUOTE = 0x10,
	TK_DQUOTE = 0x20,
	TK_OPPAR = 0x40,
	TK_CLPAR = 0x80,
	TK_LESS = 0x100,
	TK_GREAT = 0x200,
	TK_DLESS = 0x400,
	TK_DLESS2 = 0x800,
	TK_DGREAT = 0x1000,
	TK_DAMP = 0x2000,
	TK_DPIPE = 0x4000,
	TK_REDIR = 0x10000,
	TK_ESC = 0x20000,
	TK_COMPND = 0x40000,
	TK_LIST = 0x80000,
	TK_EXP = 0x100000,
	TK_NL = 0x200000,
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
	RD_IN = 0x01,
	RD_OUT = 0x02,
	PIPE_IN = 0x04,
	PIPE_OUT = 0x08,
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
typedef struct s_io		t_io;
typedef struct s_sig	t_sig;

extern t_sig			g_sig;

struct	s_sig
{
	int		exit_status;
};

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

struct	s_io
{
	int		flag;
	char	*delim;
	int		std_in;
	int		std_out;
	int		redir[2];
	int		pipe[2];
};

struct	s_param
{
	char	*path;
	t_list	*redir;
	t_list	*arg;
	t_list	*assign;
	t_io	io;
	bool	to_exec;
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

struct	s_vars
{
	t_lexer		lexer;
	t_parser	parser;
	t_ast		*exec_tree;
	t_list		*ptr_list;
	t_env		*env;
	t_env		*exp;
	t_env		*agn;
	t_io		io;
	int			nb_pipes;
	int			pipes_fd[MAX_FD];
};

#endif
