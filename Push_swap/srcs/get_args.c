/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/13 12:40:34 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*get_str(int argc, char **argv)
{
	int			i;
	int			len;
	char		*s;

	len = 0;
	i = 0;
	while (++i < argc)
	{
		len += ft_strlen(argv[i]) + 1;
		if (argv[i][0] == 0)
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
	}
	s = ft_calloc(len, sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (++i < argc)
	{
		ft_strlcat(s, argv[i], len);
		ft_strlcat(s, " ", len);
	}
	return (s);
}

int	free_strs(char **ss)
{
	char	**ss0;

	ss0 = ss;
	while (*ss)
		free(*(ss++));
	free(ss0);
	return (0);
}

int	*get_array(char *s, int *len)
{
	int		i;
	int		*ini;
	char	**ss;
	char	**ss0;

	ss = ft_split(s, ' ');
	free(s);
	if (!ss)
		return (0);
	ss0 = ss;
	*len = 0;
	while (*ss++)
		(*len)++;
	ss = ss0;
	ini = malloc(sizeof(int) * (*len));
	if (!ini)
	{
		free_strs(ss);
		return (0);
	}
	i = -1;
	while (*ss)
		ini[++i] = get_arg(*ss++, ini, ss0);
	free_strs(ss0);
	return (ini);
}

t_stack	*get_args(int argc, char **argv)
{
	int		*ini;
	int		len;
	char	*s;
	t_stack	*st;

	s = get_str(argc, argv);
	if (!s)
		return (0);
	ini = get_array(s, &len);
	if (!ini)
		return (0);
	st = new_stack(ini, len);
	if (!st)
		return (0);
	if (!get_abs_position(st))
	{
		st->free(st);
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	return (st);
}
