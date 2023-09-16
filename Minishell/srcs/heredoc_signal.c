/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 16:44:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
		exit(130);
}

void	signal_heredoc(void)
{
	struct sigaction	act;

	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	convert_heredoc(t_m *m)
{
	int		fd;
	int		ret;
	char	*s;
	char	*s0;
	char	buffer[BUFFER_SIZE + 1];

	ret = 1;
	fd = open(m->heredocf, O_RDONLY);
	if (fd == -1)
		return (0);
	s = 0;
	while (ret)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = 0;
		s = strjoinm(s, buffer, -1, -1);
	}
	s0 = str_env2(s, ft_strlen(s), m);
	close(fd);
	fd = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	write(fd, s0, ft_strlen(s0));
	close(fd);
	free(s);
	free(s0);
	return (1);
}

void	fn_heredoc(t_m *m)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_itoa(i);
	ft_strlcpy(m->heredocf, s, ft_strlen(s) + 1);
	free(s);
	while (access(m->heredocf, F_OK) != -1 && i < 100)
	{
		s = ft_itoa(++i);
		ft_strlcpy(m->heredocf, s, ft_strlen(s) + 1);
		free(s);
	}
}

char	*remove_dollar(char *s)
{
	char	*n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "$$", 2))
		{
			n = strjoinm(n, &s[i], -1, 2);
			i++;
		}
		else if (!(s[i] == '$' && ft_strchr("\'\"", s[i + 1])))
			n = strjoinm(n, &s[i], -1, 1);
		if (s[i])
			i++;
	}
	return (n);
}
