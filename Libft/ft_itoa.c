/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:11:40 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/11 22:20:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	get_num(int len, int n, char *s, int level)
{
	int i = 0;
	char *base;
	
	base = "0123456789";
	if (n != 0)
	{
		get_num(len, (n - n % 10) / 10, s, level + 1);
		i++;
	}
	s[len - 1 - level] = base[n % 10];
}

int	get_len(int n)
{
	int i = 0;

	while (n != 0)
	{
		n = (n - n % 10)/10;
		i++;
	}
	return i;
}

char	*ft_itoa(int n)
{
	int	i;
	char	*s;

	if (n == 0)
		return ("0");
	if (n >= 0)
	{
		i = get_len(n);
		s = malloc(sizeof(char) * (i + 1));
		get_num(i, n, s, 0);
		s[i] = 0;
	}
	else
	{
		i = get_len(-n);
		s = malloc(sizeof(char) * (i + 2));
		get_num(i, -n, &s[1], 0);
		s[0]='-';
		s[i+1] = 0;
	}
	return (s);
}
