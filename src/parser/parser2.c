/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:57:14 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/15 18:40:02 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	unquote_arg_list(t_list *lst)
{
	char	*s;
	char	*str;
	int		state;
	t_token	*token;

	state = ST_GENERAL;
	while (lst)
	{
		token = (t_token *)(lst->content);
		str = token->data;
		s = str;
		while (*s)
		{
			if (state_check2(&state, *s) == false)
				*str++ = *s;
			s++;
		}
		*str = '\0';
		lst = lst->next;
	}
}

void	clean_arg_list(t_list **args)
{
	t_list	*lst;
	t_list	*prev;
	t_token	*token;

	lst = *args;
	prev = NULL;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (!token->data || !(*(token->data)))
		{
			if (prev == NULL)
				*args = lst->next;
			else
				prev->next = lst->next;
			lst = lst->next;
			continue ;
		}
		prev = lst;
		lst = lst->next;
	}
}

void	new_arg_list(t_vars *vars, t_list **args, char *word, int state)
{
	t_token	*token;
	t_list	*lst;

	token = lst_alloc(1, sizeof(*token), vars);
	token->type = TK_WORD;
	token->data = word;
	if (state == ST_WILD)
		token->type |= TK_EXP;
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->content = token;
	lst->next = NULL;
	ft_lstadd_back(args, lst);
}

t_list	*word_splitting(t_vars *vars, char *buffer)
{
	char	*buf;
	char	*word;
	int		state;
	t_list	*lst;

	buf = buffer;
	lst = NULL;
	state = ST_GENERAL;
	while (*buf)
	{
		state_check2(&state, *buf);
		if ((*buf == ' ') && ((state == ST_GENERAL) || (state == ST_WILD)))
		{
			word = lst_alloc((buf - buffer) + 1, sizeof(*word), vars);
			ft_strlcpy(word, buffer, (buf - buffer) + 1);
			new_arg_list(vars, &lst, word, state);
			buffer = buf + 1;
		}
		buf++;
	}
	word = lst_alloc((buf - buffer) + 1, sizeof(*word), vars);
	ft_strlcpy(word, buffer, (buf - buffer) + 1);
	new_arg_list(vars, &lst, word, state);
	return (lst);
}
