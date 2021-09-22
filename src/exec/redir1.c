/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:04:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/22 17:28:32 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_handle(t_cmd *cmd)
{
	if (check_flag(cmd->io_bit, RD_IN))
		dup2(cmd->redir[FD_IN], FD_IN);
	if (check_flag(cmd->io_bit, RD_OUT))
		dup2(cmd->redir[FD_OUT], FD_OUT);
}
