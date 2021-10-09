/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:04:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/01 18:18:01 by flohrel          ###   ########.fr       */
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

void	close_redir(t_io *io)
{
	if (check_flag(io->flag, RD_IN))
		close(io->redir[FD_IN]);
	if (check_flag(io->flag, RD_OUT))
		close(io->redir[FD_OUT]);
}
