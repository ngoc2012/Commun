/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/22 00:06:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

sem_t	*try_open(char *s, int n)
{
	sem_t	*st;

	st = sem_open(s, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, n);
	if (st == SEM_FAILED)
	{
		sem_unlink(s);
		st = sem_open(s, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, n);
	}
	return (st);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if ((!dest) && (!src))
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_itoa(char *s, int n)
{
	int			i;
	const char	*base;

	base = "0123456789";
	if (n == 0)
	{
		s[0] = '0';
		s[1] = 0;
		return ;
	}
	i = -1;
	while (n > 0)
	{
		s[++i] = base[n % 10];
		n = n / 10;
	}
	s[++i] = 0;
}

char	*get_sem_str(const char *s, int j)
{
	char	*o;
	int		n;

	n = ft_strlen(s);
	o = malloc(sizeof(char) * (n + 6));
	if (!o)
		return (0);
	ft_memcpy(o, s, n);
	ft_itoa(&o[n], j);
	return (o);
}
