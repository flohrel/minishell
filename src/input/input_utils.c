/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:32:35 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/08 20:34:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	display_prompt(void)
{
	if (isatty(0) && (exit_status != 130))
	{
		if (!exit_status)
			return (readline(PROMPT1));
		else
			return (readline(PROMPT2));
	}
	else
		return (readline(NULL));
}
