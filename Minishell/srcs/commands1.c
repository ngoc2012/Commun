/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:41:16 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/07 16:55:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *s, int len)
{
	char	*o;

	o = malloc(len + 1);
	if (!o)
		return (0);
	ft_memcpy(o, s, len);
	o[len] = 0;
	return (o);
}

void	print_content(void *s)
{
	printf("%s,",(char *) s);
}

int	com_check(char *s)
{
}

// Check syntax error: ( command (
// Check syntax error: ) command )
t_list	*split_ops(char *s, t_m *m)
{
	int		i;
	int		i0;
	int		i1;
	int		n_o;
	int		n_c;
	char	d;
	t_list	*ops;
	t_list	*ops0;
	t_list	*postfix;
	t_list	*infix;

	postfix = 0;
	infix = 0;
	ops = 0;
	while (*s && ft_strchr(" \n", *s))
		s++;
	if (ft_strchr(";&|", *s))
	{
		m->exit_code = 2;
		m->syntax_error = 1;
		return (0);
	}
	n_o = 0;
	n_c = 0;
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("()", s[i]))
		{
			d = s[i];
			if (s[i] == '(')
				n_o++;
			else
				n_c++;
			i1 = i;
			while (--i1 >= 0 && ft_strchr(" \n", s[i1]))
				;
			i1++;
			if (i1 > i0)
			{
				ft_lstadd_back(&postfix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
				if (ops && ft_strchr("&|", ((char *)ops->content)[0]))
				{
					ft_lstadd_back(&postfix, ft_lstnew(ops->content));
					ops0 = ops;
					ops = ops->next;
					free(ops0);
				}
				ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
			}
			ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i], 1)));
			if (d == ')' && ops && ((char *)ops->content)[0] == '(')
			{
				ops0 = ops;
				ops = ops->next;
				free(ops0->content);
				free(ops0);
				if (ops && ft_strchr("&|", ((char *)ops->content)[0]))
				{
					ft_lstadd_back(&postfix, ft_lstnew(ops->content));
					ops0 = ops;
					ops = ops->next;
					free(ops0);
				}
			}
			if (d == '(')
				ft_lstadd_front(&ops, ft_lstnew(ft_strndup(&s[i], 1)));
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			if ((d == '(' && s[i] == ')') || (d == ')' && !ft_strchr(");&|", s[i])))
			{
				printf("Syntax error 1 |%c| %d |%c|\n", d, i, s[i]);
				ft_lstclear(&postfix, free);
				ft_lstclear(&infix, free);
				ft_lstclear(&ops, free);
				m->exit_code = 2;
				m->syntax_error = 1;
				return (0);
			}
			i0 = i;
		}
		else if (!ft_strncmp("&&", &s[i], 2) || !ft_strncmp("||", &s[i], 2))
		{
			i1 = i;
			while (--i1 >= 0 && ft_strchr(" \n", s[i1]))
				;
			i1++;
			if (i1 > i0)
			{
				ft_lstadd_back(&postfix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
				if (ops && ft_strchr("&|", ((char *)ops->content)[0]))
				{
					ft_lstadd_back(&postfix, ft_lstnew(ops->content));
					ops0 = ops;
					ops = ops->next;
					free(ops0);
				}
				ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
			}
			ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i], 1)));
			ft_lstadd_front(&ops, ft_lstnew(ft_strndup(&s[i], 1)));
			i++;
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			if (!s[i] || ft_strchr("&|", s[i]))
			{
				printf("Syntax error 2\n");
				ft_lstclear(&postfix, free);
				ft_lstclear(&infix, free);
				ft_lstclear(&ops, free);
				m->exit_code = 2;
				m->syntax_error = 1;
				return (0);
			}
			i0 = i;
		}
		else if (ft_strchr("\n;", s[i]))
		{
			i1 = i;
			while (--i1 >= 0 && ft_strchr(" \n", s[i1]))
				;
			i1++;
			if (i1 <= i0)
			{
				printf("Syntax error 2\n");
				ft_lstclear(&postfix, free);
				ft_lstclear(&infix, free);
				ft_lstclear(&ops, free);
				m->exit_code = 2;
				m->syntax_error = 1;
				return (0);
			}
			ft_lstadd_back(&postfix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
			ft_lstadd_back(&postfix, ft_lstnew(ft_strdup(";")));
			if (ops && ft_strchr("&|", ((char *)ops->content)[0]))
			{
				ft_lstadd_back(&postfix, ft_lstnew(ops->content));
				ops0 = ops;
				ops = ops->next;
				free(ops0);
			}
			ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i0], i1 - i0)));
			ft_lstadd_back(&infix, ft_lstnew(ft_strdup(";")));
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			if (ft_strchr(";&|", s[i]))
			{
				printf("Syntax error 4\n");
				ft_lstclear(&postfix, free);
				ft_lstclear(&infix, free);
				ft_lstclear(&ops, free);
				m->exit_code = 2;
				m->syntax_error = 1;
				return (0);
			}
			i0 = i;
		}
		else if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			if (!s[i])
				return (0);
			i++;
		}
		else
			i++;
	}
	if (i > i0)
	{
		ft_lstadd_back(&postfix, ft_lstnew(ft_strndup(&s[i0], i - i0)));
		if (ops && ft_strchr("&|", ((char *)ops->content)[0]))
		{
			ft_lstadd_back(&postfix, ft_lstnew(ops->content));
			ops0 = ops;
			ops = ops->next;
			free(ops0);
		}
		ft_lstadd_back(&infix, ft_lstnew(ft_strndup(&s[i0], i - i0)));
	}
	//printf("%d %d", n_o, n_c);
	//printf("Infix:");
	//ft_lstiter(infix, print_content);
	//printf("\nOps:");
	//ft_lstiter(ops, print_content);
	ft_lstclear(&infix, free);
	ft_lstclear(&ops, free);
	if (n_o != n_c)
		return (0);
	return (postfix);
}
