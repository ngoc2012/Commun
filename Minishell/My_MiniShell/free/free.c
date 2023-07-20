/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:38 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:34:51 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*pop_front_dlist(t_cmdIndex *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	if (index->nb_cmd == 0 || index->begin == NULL)
		return (tmp);
	if (index->nb_cmd == 1)
	{
		free(tmp->cmd);
		if (tmp->redir)
		{
			free(tmp->just_cmd);
			free_redir(tmp->lredir);
		}
		free_tab(tmp->argv);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free(tmp->cmd);
		if (tmp->redir)
		{
			free(tmp->just_cmd);
			free_redir(tmp->lredir);
		}
		free_tab(tmp->argv);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->nb_cmd--;
	return (tmp);
}

void	free_list(t_cmdIndex *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(index);
		free(tmp);
	}
	free(index);
	index = NULL;
}

void	free_list_second(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmdIndex->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(data->cmdIndex);
		free(tmp);
	}
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

t_env	*pop_front_dlist_env(t_envSom *index)
{
	t_env	*tmp;

	tmp = index->begin;
	if (index->size == 0)
		return (tmp);
	if (index->size == 1)
	{
		free(tmp->name);
		free(tmp->name_split);
		free(tmp->value_split);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free(tmp->name);
		free(tmp->name_split);
		free(tmp->value_split);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->size--;
	return (tmp);
}

void	data_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env->begin;
	while (tmp)
	{
		tmp = pop_front_dlist_env(data->env);
		free(tmp);
	}
	free(data->env);
	data->env = NULL;
}

t_redir	*pop_front_dlist_redir(t_redirIndex *redir)
{
	t_redir	*tmp;

	tmp = redir->begin;
	if (redir->size == 0)
		return (tmp);
	if (redir->size == 1)
	{
		free(tmp->file);
		redir->begin = NULL;
		redir->end = NULL;
	}
	else
	{
		free(tmp->file);
		redir->begin = redir->begin->next;
		redir->begin->back = NULL;
	}
	redir->size--;
	return (tmp);
}

void	free_redir(t_redirIndex *redir)
{
	t_redir	*tmp;

	tmp = redir->begin;
	while (tmp)
	{
		tmp = pop_front_dlist_redir(redir);
		free(tmp);
	}
	free(redir);
	redir = NULL;
}

void	free_everything(t_data *data)
{
	data_env(data);
	if (data->cmdIndex)
		free_list(data->cmdIndex);
	if (data->path_exec != NULL)
		free_tab(data->path_exec);
}
