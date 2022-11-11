/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:21:28 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/11 10:49:29 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_free_strs(char **strs0)
{
	char	**strs;

	if (strs0)
	{
		strs = strs0;
		while (*strs)
		{
			printf("free %s", *strs);
			free(*strs);
			strs++;
		}
		free(*strs);
		free(strs0);
	}
}
