/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_priorities_operators.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:25:15 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/13 11:33:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_blocked(t_list *ops, t_m *m, t_p *p)
{
	if (!(p->blocked != -1 && p->level < p->blocked))
	{
		if (((char *)ops->content)[0] == ';'
				|| (!m->exit_code && ((char *)ops->content)[0] == '&')
				|| (m->exit_code && ((char *)ops->content)[0] == '|'))
		{
			if (p->level <= p->blocked)
				p->blocked = -1;
		}
		else
			p->blocked = p->last_level;
	}
}

/*
Parse the () in command line to choose the command to execute.
A command is a string between between || ; and &&.
//printf("p |%s|\n", (char *)p->content);
//printf("pipes |%s|\n", (char *)p->content);
*/
int	infix_priorities_operators(t_list *ops, t_m *m)
{
	t_p	p;

	p.blocked = -1;
	p.level = 0;
	p.last_level = 0;
	while (ops)
	{
		if (ops->content && ((char *)ops->content)[0] == '(')
			p.level++;
		else if (ops->content && ((char *)ops->content)[0] == ')')
			p.level--;
		else if (ops->content && ft_strchr(";&|", ((char *)ops->content)[0]))
			check_blocked(ops, m, &p);
		else if (ops->content && !ft_strchr(";&|", ((char *)ops->content)[0])
				&& p.blocked == -1)
		{
			if (!pipes((char *)ops->content, m))
				return (0);
			p.last_level = p.level;
		}
		ops = ops->next;
	}
	return (1);
}
