/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/05 11:26:40 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcards(char *s, t_list **args, t_m *m)
{
	char	**ss;
	char	*s0;
	int		found;
	int		i;

	if (!s)
		return ;
	found = 0;
	if (!getcwd(m->cwd, sizeof(m->cwd)))
		return ;
	ss = ft_split(s, '*');
	i = -1;
	while (ss[++i])
	{
		s0 = remove_quotes(ss[i], ft_strlen(ss[i]));
		free(ss[i]);
		ss[i] = s0;
	}
	if (!wild_files_list(m, s, ss, args))
		ft_lstadd_back(args, ft_lstnew(ft_strdup(s)));
	free(s);
	free_array_str(&ss, 1);
}
