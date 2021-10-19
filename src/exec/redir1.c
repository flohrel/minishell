/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:04:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/19 19:16:15 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_handle(t_io *io)
{
	if (check_flag(io->flag, RD_IN))
		dup2(io->redir[FD_IN], FD_IN);
	if (check_flag(io->flag, RD_OUT))
		dup2(io->redir[FD_OUT], FD_OUT);
}

int	close_redir(t_io *io)
{
	if (check_flag(io->flag, RD_IN))
		if (close(io->redir[FD_IN]) == -1)
			return (-1);
	if (check_flag(io->flag, RD_OUT))
		if (close(io->redir[FD_OUT]) == -1)
			return (-1);
	return (0);
}

void	hdoc_copy(t_vars *vars, char **buf, char *str, bool has_exp)
{
	while (*str)
	{
		if ((*str == '$') && (has_exp == true))
			var_expansion(vars, buf, &str);
		else
			**buf = *str;
		(*buf)++;
		str++;
	}
}

int	parse_redir2(t_vars *vars, t_param *param, t_token *token)
{
	int	ret;

	ret = 0;
	if (close_redir(&param->io) == -1)
		return (-1);
	if (check_flag(token->type, TK_GREAT))
		ret = set_rdout(&param->io, token->data);
	else if (check_flag(token->type, TK_DGREAT))
		ret = set_rdapp(&param->io, token->data);
	else if (check_flag(token->type, TK_LESS))
		ret = set_rdin(&param->io, token->data);
	else
	{
		if (check_flag(token->type, TK_DLESS2))
			ret = set_hdoc(vars, &param->io, token->data, false);
		else
			ret = set_hdoc(vars, &param->io, token->data, true);
	}
	return (ret);
}
