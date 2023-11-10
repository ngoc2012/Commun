/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:21:18 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 16:00:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Configuration.hpp"

int	main()
{
	vector<Configuration>	confs;
	confs.push_bask(Configuration("127.0.0.1", 4242));
	confs.push_bask(Configuration("127.0.0.1", 4141));
	Server server();
	server.set_confs(confs);
	return (0);
}
