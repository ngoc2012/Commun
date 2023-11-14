/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:21:18 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 18:13:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "Host.hpp"
#include "Server.hpp"
#include "ConfigurationParser.hpp"

/*
Host	*g_host;

void	main_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "", 0);
		g_host->set_end_host(true);
		g_host->end();
	}
}
*/

int	main()
{
	std::vector<Server>	servers;
	ConfigurationParser	parser(servers, ".conf");
	/*
	struct sigaction	act;
	act.sa_flags = SA_RESTART;
	act.sa_handler = main_signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	std::vector<Server>	servers;
	servers.push_back(Server("127.0.0.1", 4242));
	servers.push_back(Server("127.0.0.1", 4141));
	Host host(&servers);
	g_host = &host;
	host.start();
	*/
	return (0);
}
