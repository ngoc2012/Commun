/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:21:18 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/26 11:09:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "Host.hpp"
#include "Server.hpp"
#include "ConfigurationParser.hpp"

Host	*g_host;

void	main_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "", 0);
		//g_host->end();
	}
	if (sig == SIGPIPE)
	{
		std::map<int, Response*>	sk_response = g_host->get_sk_response();
		std::map<int, ClientRequest*>	sk_client_request = g_host->get_sk_client_request();
		for (std::map<int, ClientRequest*>::iterator	it = sk_client_request.begin();
			it != sk_client_request.end(); ++it)
			g_host->close_client_sk(it->first);
		for (std::map<int, Response*>::iterator	it = sk_response.begin();
			it != sk_response.end(); ++it)
			g_host->delete_response(it->first);
	}
}

int	main()
{
	struct sigaction	act;
	act.sa_flags = SA_RESTART;
	act.sa_handler = main_signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	Host			host(".conf");
	g_host = &host;
	host.start();
	return (0);
}
