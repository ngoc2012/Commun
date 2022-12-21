/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/21 05:04:31 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"

/*
sa (swap a) : Intervertit les 2 premiers éléments au sommet de la pile a.
Ne fait rien s’il n’y en a qu’un ou aucun.
sb (swap b ) : Intervertit les 2 premiers éléments au sommet de la pile b.
Ne fait rien s’il n’y en a qu’un ou aucun.
ss : sa et sb en même temps.
pa (push a) : Prend le premier élément au sommet de b et le met sur a.
Ne fait rien si b est vide.
pb (push b) : Prend le premier élément au sommet de a et le met sur b.
Ne fait rien si a est vide.
ra (rotate a) : Décale d’une position vers le haut tous les élements de la pile a.
Le premier élément devient le dernier.
rb (rotate b) : Décale d’une position vers le haut tous les élements de la pile b.
Le premier élément devient le dernier.
rr : ra et rb en même temps.
rra (reverse rotate a) : Décale d’une position vers le bas tous les élements de
la pile a. Le dernier élément devient le premier.
rrb (reverse rotate b) : Décale d’une position vers le bas tous les élements de
la pile b. Le dernier élément devient le premier.
rrr : rra et rrb en même temps.
*/

typedef struct s_stack	t_stack;

struct s_stack
{
	int	*ini;
	int	*current;
	int	*position;
	int	*sorted;
	int	push;
	int	len;
	void	(*get_position)(t_stack *);
	void	(*print)(t_stack *);
	void	(*free)(t_stack *);
};

void	print_stack(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
	{
		if (i == st->push)
			ft_printf("   -------\n");
		ft_printf("%5d", st->current[i]);
		if (st->len - st->position[i] < st->position[i])
			ft_printf("%5d", st->position[i] - st->len);
		else
			ft_printf("%5d", st->position[i]);
		ft_printf("\n");
	}
	ft_printf("%5s", "___");
	ft_printf("%5s", "___");
	ft_printf("\n");
	ft_printf("%5s", "ini");
	ft_printf("%5s", "pos");
	ft_printf("\n");
	ft_printf("----------\n");
	/*
	i = -1;
	while (++i < st->len)
	{
		if (i > st->push - 1)
			ft_printf("%5d", st->current[i]);
		if (i > st->len - 1 - st->push)
			ft_printf("%5d", st->current[st->len - 1 - i]);
		if (i > st->push - 1 || i > st->len - st->push - 1)
			ft_printf("\n");
	}
	ft_printf("%5c", '_');
	ft_printf("%5c", '_');
	ft_printf("\n");
	ft_printf("%5c", 'a');
	ft_printf("%5c", 'b');
	ft_printf("\n");
	ft_printf("----------\n");
	*/
}

int	*cp_array(int *ini, int len)
{
	int	*new;
	
	new = malloc(sizeof(int) * len);
	if (!new)
		return (0);
	while (--len >= 0)
		new[len] = ini[len];
	return (new);
}

void	free_stack(t_stack *st)
{
	free(st->ini);
	free(st->current);
	free(st->position);
	free(st);
}

void	get_position(t_stack *st)
{
	int		i;
	int		j;

	i = -1;
	while (++i < st->len)
	{
		st->position[i] = 0;
		j = -1;
		while (++j < i)
		{
			if (st->ini[j] > st->ini[i])
				st->position[i]++;
		}
	}
}

t_stack	*new_stack(int *ini, int len)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->ini = ini;
	new->current = cp_array(ini, len);
	new->position = malloc(sizeof(int) * len);
	if (!new->position)
		return (0);
	new->len = len;
	new->push = 0;	
	new->get_position = get_position;
	new->print = print_stack;
	new->free = free_stack;
	return (new);
}

int	main(int argc, char **argv)
{
	int		i;
	//int		j;
	int		fd;
	int		*ini;
	t_stack		*st;
	char	*s;

	if (argc < 2)
		return (1);
	ini = malloc(sizeof(int) * (argc - 1));
	if (!ini)
		return (0);
	i = 1;
	while (i < argc)
	{
		ini[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	st = new_stack(ini, argc - 1);
	if (!st)
		return (0);
	st->get_position(st);
	st->print(st);
	fd = open("operations.txt", O_RDONLY);
	while ((s = get_next_line(fd)))
	{
		if (s[ft_strlen(s) - 1] == '\n')
			s[ft_strlen(s) - 1] = 0;
		/*
		ft_printf("%s :\n", s);
		if ((ft_strncmp(s, "sa", 2) == 0 || ft_strncmp(s, "ss", 2) == 0) && st->len - st->push >= 2)
		{
			j = st->current[st->push];
			st->current[st->push] = st->current[st->push + 1]; 
			st->current[st->push + 1] = j;
			st->print(st);
		}
		if ((ft_strncmp(s, "sb", 2) == 0 || ft_strncmp(s, "ss", 2) == 0) && st->push >= 2)
		{
			j = st->current[st->push - 1];
			st->current[st->push - 1] = st->current[st->push - 2]; 
			st->current[st->push - 2] = j;
			st->print(st);
		}
		if (ft_strncmp(s, "pa", 2) == 0 && st->push > 0)
		{
			st->push--;
			st->print(st);
		}
		if (ft_strncmp(s, "pb", 2) == 0 && st->push < st->len)
		{
			st->push++;
			st->print(st);
		}
		if ((ft_strncmp(s, "ra", 3) == 0 || ft_strncmp(s, "rr", 3) == 0) && st->len - st->push >= 2)
		{
			//ft_printf("ra\n");
			i = st->push;
			while (i < st->len - 1)
			{
				j = st->current[i];
				st->current[i] = st->current[i + 1]; 
				st->current[i + 1] = j;
				i++;
			}
			st->print(st);
		}
		if ((ft_strncmp(s, "rrb", 3) == 0 || ft_strncmp(s, "rrr", 3) == 0) && st->push >= 2)
		{
			//ft_printf("rrb\n");
			i = 0;
			while (i < st->push - 1)
			{
				j = st->current[i];
				st->current[i] = st->current[i + 1]; 
				st->current[i + 1] = j;
				i++;
			}
			st->print(st);
		}
		if ((ft_strncmp(s, "rra", 3) == 0 || ft_strncmp(s, "rrr", 3) == 0) && st->len - st->push >= 2)
		{
			//ft_printf("rra\n");
			i = st->len - 1;
			while (i > st->push)
			{
				j = st->current[i];
				st->current[i] = st->current[i - 1]; 
				st->current[i - 1] = j;
				i--;
			}
			st->print(st);
		}
		if ((ft_strncmp(s, "rb", 3) == 0 || ft_strncmp(s, "rr", 3) == 0) && st->push >= 2)
		{
			//ft_printf("rb\n");
			i = st->push - 1;
			while (i > 0)
			{
				j = st->current[i];
				st->current[i] = st->current[i - 1]; 
				st->current[i - 1] = j;
				i--;
			}
			st->print(st);
		}
	*/
		free(s);
	}
	st->free(st);
}
