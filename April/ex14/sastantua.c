/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sastantua.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:07:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/04 10:05:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	ft_atoi(const char *str)
{
	int		nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*str == 9 || *str == 10 || *str == 11
		|| *str == 12 || *str == 13 || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0' && (*str >= 48 && *str <= 57))
	{
		if (*str >= 48 && *str <= 57)
		{
			nbr *= 10;
			nbr += *str - 48;
		}
		str++;
	}
	return (sign * nbr);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int n = ft_atoi(argv[1]);
	int spaces = 0;
	for (int i = 0; i < n; i++)
	{
		spaces += 2 + i; // height
		spaces += 3 + i / 2; // bord
	}
	spaces -= 3 + (n - 1) / 2;
	int stars = 1;
	int h_floor = 3;
	int door = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < h_floor; j++)
		{
			for (int k = 0; k < spaces; k++)
				write(1, " ", 1);
			spaces--;
			write(1, "/", 1);
			for (int k = 0; k < stars; k++)
			{
				if (i == (n - 1) && j >= h_floor - door
						&& k >= stars / 2 - door / 2 && k <= stars / 2 + door / 2)
				{
					if (n > 4 && j == h_floor - door / 2 - 1 && k == stars / 2 + door / 2 - 1)
						write(1, "$", 1);
					else
						write(1, "|", 1);
				}
				else
					write(1, "*", 1);
			}
			write(1, "\\\n", 2);
			stars += 2;
		}
		h_floor++;
		spaces -= 2 + i / 2;
		stars += 2*(2 + i / 2);
		if (i % 2 == 1)
			door += 2;
	}
}
