/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_priorities_operators.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:25:15 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/08 14:42:42 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parse the () in command line to choose the command to execute.
A command is a string between between || ; and &&.
i			b=1 b=2			  b=1          b=0
(echo 1   &&  echo 2 ||  (   (  echo  4  && echo 5 )  && echo 6 ) && echo 7 )
*/
static void	parentheses(t_list **ops, int *blocked)
{
	int	b;

	*ops = (*ops)->next;
	if (*blocked)
	{
		b = 1;
		while (*ops && b)
		{
			if (!ft_strncmp("(", (char *)(*ops)->content, 2))
				b++;
			if (!ft_strncmp(")", (char *)(*ops)->content, 2))
				b--;
			*ops = (*ops)->next;
		}
		*blocked = 0;
	}
}

static int	operators(t_list **ops, t_m *m, int *blocked)
{
	if (!ft_strncmp("&&", (char *)(*ops)->content, 3))
	{
		if (m->exit_code)
			*blocked = 1;
		else
			*blocked = 0;
		*ops = (*ops)->next;
		return (1);
	}
	else if (!ft_strncmp("||", (char *)(*ops)->content, 3))
	{
		if (m->exit_code)
			*blocked = 0;
		else
			*blocked = 1;
		*ops = (*ops)->next;
		return (1);
	}
	return (0);
}

int	infix_priorities_operators(t_list *ops, t_m *m)
{
	int	blocked;

	blocked = 0;
	while (ops)
	{
		if (operators(&ops, m, &blocked))
			;
		else if (!ft_strncmp("(", (char *)ops->content, 2))
			parentheses(&ops, &blocked);
		else if (!ft_strncmp(")", (char *)ops->content, 2))
			ops = ops->next;
		else if (!blocked)
		{
			if (!pipes((char *)ops->content, m))
				return (0);
			ops = ops->next;
		}
		else
		{
			ops = ops->next;
			blocked = 0;
		}
	}
	return (1);
}
