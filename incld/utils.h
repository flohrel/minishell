/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:36:25 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/18 04:00:59 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "data.h"
# include "lexer.h"
# include "ansi_colors.h"

/*
 **		exit.c
 */
void	free_cmd(t_cmd **data);
void	free_vars(t_lexer *lexer, t_parser *parser);
void	clean_exit(t_vars *vars, int status);

/*
 **		token.c
 */
char	get_token_char(int type);
int		get_token_type(char c);
void	new_token(t_vars *vars, int type, int size);
void	del_token(void *content);

/*
 **		astree.c
 */
t_ast	*tree_new_node(t_vars *vars, int type, t_cmd *data);
void	tree_attach_branch(t_ast *root, t_ast *left, t_ast *right);
void	tree_delete_node(t_ast *node);

/*
 **		test.c
 */
void	display_token_list(t_lexer *lexer);

#endif
