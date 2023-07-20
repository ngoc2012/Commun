/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:42 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:32:27 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_space(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' )
		(*i)++;
}

//regarde si cest la fin d'une string pour les redirection
int	is_end_redir(char c)
{
	if (c == '\0' || c == '<' || c == '>')
	{
		ft_putstr_fd(ERROR_TOKEN, 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	no_str(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '\0')
		return (1);	
	return (0);
}

int others_char(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '>' || cmd[i] == '<'
		|| cmd[i] == ';' || cmd[i] == '&' || cmd[i] == '|' || cmd[i] == '('
		|| cmd[i] == ')')
		i++;
	if (cmd[i] == '\0')
	{
		ft_putstr_fd(ERROR_TOKEN, 2);
		return (1);
	}
	return (0);
}

void	get_file(char *str, int *i)
{
	while (str[*i] && str[*i] != '>' && str[*i] != '<' && str[*i] != ' ')
	{
		if (str[*i] == '"' || str[*i] == '\'')
			(*i) = parseur_quotes(str, *i + 1, str[*i]);
		(*i)++;
	}
}

void	printTitle(void)
{
	printf(".-.   .-..-..-. .-..-. .----..-. .-..----..-.   .-.\n");
	printf("|  `.'  || ||  `| || |{ {__  | {_} || {_  | |   | |\n");
	printf("| |\\ /| || || |\\  || |.-._} }| { } || {__ | `--.| |--.\n");
	printf("`-' ` `-'`-'`-' `-'`-'`----' `-' `-'`----'`----'`----'\n");
}
