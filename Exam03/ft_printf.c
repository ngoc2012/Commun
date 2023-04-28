/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:09:56 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/04/27 15:25:17 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (*(s++))
		i++;
	return (i);
}

int	ft_printf(char *s, ...)
{
	va_list	ap;
	int	n = 0;


	va_start(ap, s);
	write(1, s, ft_strlen(s));
	n += ft_strlen(s);
	//s = va_arg(ap, char *);
	va_end(ap);
	return (n);
}

int	main()
{
	int n;
	n = ft_printf("test\n");
	printf("%d\n", n);
}
