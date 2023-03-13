/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/13 12:46:03 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	arg_error(int *ini)
{
	ft_printf("Error\n");
	free(ini);
	exit(EXIT_FAILURE);
}

char	*get_str(char *s)
{
	char	*s0;
	char	sign;

	sign = 0;
	if (*s == '+' || *s == '-')
		sign = *s++;
	if (*s == 0)
		return (0);
	while (*s == '0' && s[1] != 0)
		s++;
	s0 = s;
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	if (sign == '-' && ft_strncmp(s0, "0", 2) != 0)
		*(--s0) = sign;
	return (s0);
}

int	get_arg(char *s, int *ini, char **ss)
{
	int		i;
	char	*s0;
	char	*s1;

	s0 = get_str(s);
	if (!s0)
	{
		free_strs(ss);
		arg_error(ini);
	}
	i = ft_atoi(s0);
	s1 = ft_itoa(i);
	if (ft_strncmp(s1, s0, ft_strlen(s0)) != 0)
	{
		free(s1);
		free_strs(ss);
		arg_error(ini);
	}
	free(s1);
	return (ft_atoi(s0));
}
