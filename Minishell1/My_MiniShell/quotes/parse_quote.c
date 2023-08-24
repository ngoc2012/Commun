/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:11:54 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:13:24 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_cmd(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = parseur_quotes(str, i + 1, str[i]);
		if (str[i] == '|')
			j++;
		i++;
	}
	return (j);
}

void	splitage_quote(t_cmdIndex *cmdI, char *str)
{
	char	*cmd;
	int		i;
	int		start;
	int		q;
	char	*tmp;

	i = 0;
	start = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = parseur_quotes(str, i + 1, str[i]);
			q = 1;
		}
		if (str[i] == '|' || str[i + 1] == '\0')
		{
			cmd = ft_substr(str, start, i - start + 1);
			tmp = ft_strtrim(cmd, "|");
			free(cmd);
			cmd = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strtrim(cmd, " ");
			free(cmd);
			cmd = ft_strdup(tmp);
			free(tmp);
			start = i;
			pushback_cmd(cmd, cmdI, q);
			free(cmd);
			q = 0;
		}
		i++;
	}
}

int	split_quotes(char *str, t_cmdIndex *cmdIndex)
{
	int	nb_cmd;

	nb_cmd = 0;
	if (count_double_quote(str) == 1 || count_simple_quote(str) == 1)
		return (-1);
	nb_cmd = how_many_cmd(str);
	if (nb_cmd == -1)
	{
		ft_putstr_fd("Error: pipe\n", 2);
		return (nb_cmd);
	}
	else if (nb_cmd == 1)
	{
		pushback_cmd(str, cmdIndex, 1);
		return nb_cmd;
	}
	else
	{
		splitage_quote(cmdIndex, str);
		return nb_cmd;
	}
}
