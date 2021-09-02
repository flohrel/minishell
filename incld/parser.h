/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:59:00 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/11 22:44:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <stdbool.h>
# include "data.h"
# include "lexer.h"
# include "exec.h"
# include "utils.h"
# include "test.h"

/*
 **		parser_utils.c
 */
void	state_check(int *state, char c);
char	*exit_status_expansion(t_vars *vars, char **str, int exit_status);
void	var_expansion(t_vars *vars, char **buffer, char **data);
char	*var_assignation(t_vars *vars, char *data, char *str);
int		check_token(t_parser *parser, int type);

/*
 **		parser.c
 */
int		parser(t_vars *vars, t_lexer *lexer, t_parser *parser);
int		parse_word(t_vars *vars, t_list *prev_tk, char **data);
void	param_expansion(t_vars *vars, char *str, char *buffer);
void	path_expansion(t_vars *vars, char *str, char *buffer);
int		clean_empty_word(t_vars *vars, char **data, char *buffer);

/*
 **		ast_build0.c
 */
int		astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser);

/*
 **		ast_build1.c
 */
t_ast	*list(t_vars *vars, t_parser *parser);
t_ast	*list1(t_vars *vars, t_parser *parser);
t_ast	*list2(t_vars *vars, t_parser *parser);
t_ast	*job(t_vars *vars, t_parser *parser);
t_ast	*pipeline(t_vars *vars, t_parser *parser);

/*
 **		ast_build2.c
 */
t_ast	*cmd(t_vars *vars, t_parser *parser);
bool	is_valid_name(char *data, char *end);
void	argument(t_vars *vars, t_token *token, t_param *data);
int		redirection(t_vars *vars, t_parser *parser, int type, t_param *data);
t_param	*init_cmd_param(t_vars *vars);

/*
 **		wildcard.c
 */
char	*wildcard(t_vars *vars, char *str);
char	**find_matches(t_vars *vars, DIR *dir, char *str);
char	*find_match(char *file_name, char *str);
int		search_match(char *file_name, char *str, int i, int j);
int		open_curdir(DIR **cur_dir);

#endif
