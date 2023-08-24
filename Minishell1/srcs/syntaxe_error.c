/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:32:35 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 16:09:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntaxe_error(t_m *m)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	m->exit_code = 2;
	if (m->infix)
		ft_lstclear(&m->infix, free);
	if (m->coms)
		return (free_array_str(&m->coms, 0));
	return (0);
}
