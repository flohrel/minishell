/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:32:35 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/09 17:32:21 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*display_prompt(void)
{
	if (isatty(0))
	{
		if (!g_sig.exit_status)
			return (readline(PROMPT1));
		else
			return (readline(PROMPT2));
	}
	else
		return (readline(NULL));
}
