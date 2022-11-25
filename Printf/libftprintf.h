/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 05:49:12 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>

typedef struct	s_printf
{
	va_list	ap;
	int	ar;
	int	i;
	int	start;
	int	limit;
	int	size;
	char	type;
	char	fill;
	char	prefix;
	char	*str;
	char	*str2;
	char	*types;
	char	*flag;
	char	*all_flags;
	char	*base10;
	char	*hex;
	char	*HEX;
	char	*numbers;
	t_list	*out;
	t_list	*out0;
	t_list	*last;
}	t_printf

char	*ft_usitoa(unsigned int n);
char	*ft_itoa_base(char *base, void *nbr);
int	ft_printf(const char *s, ...);

#endif
