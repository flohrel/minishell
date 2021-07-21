/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:30:44 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 04:26:05 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_list *lst, t_vars *vars)
{
	char	**result;
	int		i;
	int		size;
	t_token	*token;

	size = ft_lstsize(lst);
	i = 0;
	result = lst_alloc(size + 1, sizeof(char *), vars);
	if (!result)
		return (NULL);
	while (i < size)
	{
		token = (t_token *)lst->content;
		result[i++] = token->data;
		lst = lst->next;
	}
	result[i] = NULL;
	return (result);
}

void	*lst_alloc(size_t nmemb, size_t size, t_vars *vars)
{
	void	*ptr;

	ptr = garbage_collector(nmemb, size, &vars->ptr_list);
	if (ptr == NULL)
		clean_exit(vars, NULL, errno);
	return (ptr);
}

int	syntax_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd(": quote missing\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(" near unexpected token `", STDERR_FILENO);
		if (token->type == TK_NL)
			ft_putstr_fd("newline", STDERR_FILENO);
		else if (token->type == TK_DGREAT)
			ft_putstr_fd(">>", STDERR_FILENO);
		else
			ft_putchar_fd(get_token_char(token->type), STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	return (-1);
}
