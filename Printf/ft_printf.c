/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/23 22:19:36 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "Libft/libft.h"
#include "libftprintf.h"

char*	hex_address(char *hex, void *addr)
{
	long unsigned int i;
	long unsigned int i0;
	int		j;
	int		mod;
	char	*str;

	i = (long unsigned int) addr;
	i0 = i;
	j = 0;
	while (i != 0)
	{
		i = (i - i % 16) / 16;
		j++;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	str[j] = 0;
	i = i0;
	j--;
	while (i != 0)
	{
		mod = i % 16;
		i = (i - mod) / 16;
		str[j--] = hex[mod];
	}
	return str;
}

int	ft_printf(const char *s, ...)
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

	va_start(ap, s);
	hex = "0123456789abcdef";
	HEX = "0123456789ABCDEF";
	base10 = "0123456789";
	types = "cspdiuxX%";
	numbers = "pdiuxX";
	all_flags = "-0.# +";
	type = 0;
	prefix = 0;
	//printf("string = ###%s###\n", s);
	size = INT_MAX;
	i = 0;
	start = 0;
	out = 0;
	flag = ft_calloc(7, sizeof(char));
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (i > start)
			{
				if (out)
					ft_lstadd_back(&out, ft_lstnew(ft_substr(s, start, i - start)));
				else
					out = ft_lstnew(ft_substr(s, start, i - start));
				str = ft_substr(s, start, i - start);
				//printf("str = #%s#\n", str);
				free(str);
			}
			i++;
			//printf("%c %d %d %d\n", s[i], ft_strchr(base10, s[i]), ft_strchr(all_flags, s[i]), ft_strchr(types, s[i])); 
			while (s[i] && (ft_strchr(all_flags, s[i])) && !ft_strchr(types, s[i]))
			{
				if (s[i] == '.')
				{
					i++;
					start = i;
					while (s[i] && ft_strchr(base10, s[i]))
						i++;
					if (i > start)
					{
						str = ft_substr(s, start, i - start);
						//printf("number = %s\n", str);
						size = ft_atoi(str);
						//printf("size = %d\n", size);
						free(str);
					}
				}
				while (s[i] && (ft_strchr(all_flags, s[i])) && !ft_strchr(types, s[i]))
				{
					if (!ft_strchr(flag, s[i]))
						ft_strlcat(flag, &s[i], ft_strlen(flag) + 2);
					i++;
				}
				if (ft_strchr(base10, s[i]))
				{
					start = i;
					while (s[i] && ft_strchr(base10, s[i]))
						i++;
					str = ft_substr(s, start, i - start);
					//printf("number = %s\n", str);
					limit = ft_atoi(str);
					//printf("limit = %d\n", limit);
					free(str);
					//printf("1 s[i] = %c\n", s[i]);
				}
				if (s[i])
					i++;
			}
			if (ft_strchr(types, s[i]))
				type = s[i];
			printf("type = %c, flag = %s, flag_len = %d\n", type, flag, ft_strlen(flag)); 

			if (type == 'c')
			{
				str = ft_strdup(" ");
				str[0] = (char) va_arg(ap, int);
				ft_lstadd_back(&out, ft_lstnew(str));
			}
			if (type == 's')
			{
				str = ft_strdup((const char *) va_arg(ap, char *));
				ft_lstadd_back(&out, ft_lstnew(str));
				//printf("strlen = %d\n", ft_strlen(str));
				//last = ft_lstlast(out);
				//printf("last->content = %s\n", (char *) last->content);
			}
			if (type == 'p')
			{
				str = hex_address(hex, va_arg(ap, void *));
				str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
				ft_strlcpy(str2, "0x", 3);
				ft_strlcat(str2, str, ft_strlen(str) + 3);
				ft_lstadd_back(&out, ft_lstnew(str2));
				free(str);
			}
			if (type == 'u')
			{
				ar = va_arg(ap, int);
				if (ar >= 0)
					ft_lstadd_back(&out, ft_lstnew(ft_itoa(ar)));
				else
					ft_lstadd_back(&out, ft_lstnew(ft_usitoa(ar)));
			}
			if (type == 'i' || type == 'd')
			{
				ar = va_arg(ap, int);
				ft_lstadd_back(&out, ft_lstnew(ft_itoa(ar)));
				//last = ft_lstlast(out);
				//printf("last->content = %s\n", (char *) last->content);
			}
			if (type == 'x')
			{
				str = hex_address(hex, va_arg(ap, void *));
				if (ft_strlen(str) > 8)
					ft_memmove(str, &str[ft_strlen(str) - 8], 9);
				if (ft_strchr(flag, '#'))
				{
					str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
					ft_strlcpy(str2, "0x", 3);
					ft_strlcat(str2, str, ft_strlen(str) + 3);
					ft_lstadd_back(&out, ft_lstnew(str2));
					free(str);
				}
				else
					ft_lstadd_back(&out, ft_lstnew(str));
			}
			if (type == 'X')
			{
				str = hex_address(HEX, va_arg(ap, void *));
				if (ft_strchr(flag, '#'))
				{
					str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
					ft_strlcpy(str2, "0x", 3);
					ft_strlcat(str2, str, ft_strlen(str) + 3);
					ft_lstadd_back(&out, ft_lstnew(str2));
					free(str);
				}
				else
					ft_lstadd_back(&out, ft_lstnew(str));
			}
			if (type == '%')
				ft_lstadd_back(&out, ft_lstnew(ft_strdup("%")));
			if (ft_strchr(types, type))
			{
				last = ft_lstlast(out);
				if (size < ft_strlen(last->content))
				{
					str = ft_calloc(size + 1, sizeof(char));
					ft_strlcpy(str, last->content, size + 1);
					free(last->content);
					last->content = str;
				}
			}
			if (ft_strchr(types, type) && limit > 0)
			{
				printf("limit = %d, size  = %d\n", limit, size);
				last = ft_lstlast(out);
				if (limit > ft_strlen(last->content))
				{
					str = ft_calloc(limit + 1, sizeof(char));
					if (!str)
						return (0);
					start = limit - ft_strlen(last->content);
					if (start < 0)
						start = 0;
					fill = ' ';
					prefix = 0;
					if (ft_strchr(flag, ' '))
					{
						prefix = ' ';
					}
					if (ft_strchr(flag, '+') && ft_strchr(numbers, type))
					{
						if (!ft_memcmp(last->content, "-", 1))
							prefix = '-';
						else
							prefix = '+';
					}
					if (ft_strchr(flag, '0'))
						fill = '0';
					if (ft_strchr(flag, '-'))
					{
						start = 0;
						fill = ' ';
					}
					//printf("last->content = %s\n", (char *) last->content);
					//printf("start = %d, fill = #%c#, prefix = #%c#\n", start, fill, prefix);
					ft_memset(str, fill, limit);
					if (prefix)
						ft_memset(str, prefix, 1);
					ft_memcpy(str + start, last->content, ft_strlen(last->content));
					free(last->content);
					last->content = str;
				}
			}
			free(flag);
			start = i + 1;
		}
		if (s[i])
			i++;
	}
	//printf("i = %d, start = %d\n", i, start);
	if (i > start)
	{
		if (out)
			ft_lstadd_back(&out, ft_lstnew(ft_substr(s, start, i - start)));
		else
			out = ft_lstnew(ft_substr(s, start, i - start));
	}
	out0 = out;
	while (out)
	{
		//ft_putchar_fd('#', 1);
		ft_putstr_fd(out->content, 1);
		//ft_putchar_fd('#', 1);
		//ft_putchar_fd('\n', 1);
		out = out->next;
	}
	ft_lstclear(&out0, free);
	va_end(ap);
	return (0);
}
