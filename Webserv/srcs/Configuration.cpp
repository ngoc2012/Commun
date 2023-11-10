/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 15:56:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Configuration::Configuration()
{
	clean();
}
Configuration::Configuration(const Configuration& src) { *this = src; }
Configuration&	Configuration::operator=( Configuration const & src )
{
	(void) src;
	return (*this);
}
Configuration::~Configuration() {}
Configuration::Configuration(const char* ip, int port)
{
	_ip_address = ip;
	_port = port;
	_max_clients = 128;
}
char*			Configuration::get_ip_address(void) {return (_ip_address);}
short unsigned int	Configuration::get_port() {return (_port);}