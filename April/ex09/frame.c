/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:35:46 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/03 18:14:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_src;

	size_src = ft_strlen(src);
	if ((!dest) || (!src) || (size == 0))
		return (size_src);
	if (size_src > (size - 1))
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = 0;
	}
	else
		ft_memcpy(dest, src, size_src + 1);
	return (size_src);
}

// Get number of strings at the out put, must be 0 if all match
static int	get_n_strs(const char *str, char charset)
{
	int	i;
	int	n_strs;

	i = 0;
	n_strs = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		if (str[i])
			n_strs++;
		while (str[i] && !(str[i] == charset))
			i++;
	}
	return (n_strs);
}

// Get chunks (begin and end) of string to output
static int	get_strs(const char *str, char charset, char **out)
{
	int		i;
	int		start;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		start = i;
		while (str[i] && !(str[i] == charset))
			i++;
		if (i > start)
		{
			out[j] = malloc(sizeof(char) * (i - start + 1));
			if (!out[j])
				return (0);
			ft_strlcpy(out[j], &(str[start]), i - start + 1);
			j++;
		}
	}
	return (1);
}

char	**ft_split(const char *str, char charset)
{
	int		n_strs;
	char	**out;
	char	**out0;

	n_strs = get_n_strs(str, charset);
	out = malloc(sizeof(char *) * (n_strs + 1));
	if (!out)
		return (NULL);
	if (n_strs > 0)
	{
		if (!get_strs(str, charset, out))
		{
			out0 = out;
			while (*out)
				free(*(out++));
			free(out0);
			return (0);
		}
	}
	out[n_strs] = 0;
	return (out);
}

int	main(int argc, char *argv[]) {

	char **s;
	int max_length = 0;

	// Determine the maximum length of the input strings
	for (int i = 1; i < argc; i++) {
		char **ss = ft_split(argv[i], ' ');

		int j = -1;
		while (ss[++j])
			if (max_length < ft_strlen(ss[j]))
				max_length = ft_strlen(ss[j]);

		// Print the top border
		for (int i = 0; i < max_length + 4; i++) {
			printf("*");
		}
		printf("\n");

		// Print the strings in a frame
		j = -1;
		while (ss[++j])
		{
			printf("* %s", ss[j]);
			for (int k = ft_strlen(ss[j]); k < max_length; k++) {
				printf(" ");
			}
			printf(" *\n");
		}

		// Print the bottom border
		for (int i = 0; i < max_length + 4; i++) {
			printf("*");
		}
		printf("\n");

		j = -1;
		while (ss[++j])
			free(ss[j]);
		free(ss);
	}


	return 0;
}
