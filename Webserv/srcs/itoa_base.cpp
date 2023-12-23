/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 08:47:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/23 08:48:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	get_base(char *base)
{
	unsigned int	i;
	unsigned int	j;
	char			*c;

	c = base;
	i = 0;
	while (*base != '\0')
	{
		if (*base == '+' || *base == '-' || (!(*base >= 33 && *base <= 126)))
			return (0);
		j = 0;
		while (j < i)
		{
			if (c[j] == *base)
				return (0);
			j++;
		}
		i++;
		base++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

void	get_str(unsigned int nbr, char *base, unsigned int b)
{
	if (nbr > (b - 1))
		get_str((nbr - nbr % b) / b, base, b);
	write(1, &base[nbr % b], 1);
}

namespace ft {

void	itoa_base(int nbr, char *base)
{
	unsigned int	n;
	int				b;

	b = get_base(base);
	if (b == 0)
		return ;
	if (nbr < 0)
	{
		write(1, "-", 1);
		n = -nbr;
	}
	else
	{
		n = nbr;
	}
	get_str(n, base, b);
}

}
