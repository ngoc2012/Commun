/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:21:18 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/11 08:11:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Configuration.hpp"

Server	*g_server;

void	main_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		std::cout << "Server ended" << std::endl;

	}
}

int	main()
{
	struct sigaction	act;
	act.sa_flags = SA_RESTART;
	act.sa_handler = main_signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	std::vector<Configuration>	confs;
	confs.push_back(Configuration("127.0.0.1", 4242));
	confs.push_back(Configuration("127.0.0.1", 4141));
	Server server(&confs);
	g_server = &server;
	server.start();
	return (0);
}
