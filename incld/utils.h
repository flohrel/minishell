/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:36:25 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 14:03:21 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <term.h>
# include "data.h"
# include "lexer.h"
# include "ansi_colors.h"
# include "builtins.h"

/*
 **		exit.c
 */
void	del_hist_entry(void *content);
void	free_unlisted_vars(t_vars *vars);
void	clean_exit(t_vars *vars, int status);

/*
 **		token.c
 */
char	get_token_char(int type);
int		get_token_type(char c);
void	new_token(t_vars *vars, int type, int size);
void	del_token(void *content);
void	delete_empty_token(t_lexer *lexer, t_parser *parser);

/*
 **		astree.c
 */
t_ast	*tree_new_node(t_vars *vars, int type, t_param *data);
void	tree_attach_branch(t_ast *root, t_ast *left, t_ast *right);
void	tree_delete_node(t_ast *node);

/*
 **		error.c
 */
int		syntax_error(t_token *token);

/*
 **		memory.c
 */
void	*lst_alloc(size_t nmemb, size_t size, t_vars *vars);

/*
 **		list_to_tab.c
 */
char	**list_to_tab(t_list *lst, t_vars *vars);
void	print_tab(char **arg);

/*
 **		init.c
 */
void	init(t_vars *vars, char **envp);
void	init_term(t_vars *vars);


#endif
