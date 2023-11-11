/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/11 08:05:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

Configuration::Configuration() {}
Configuration::Configuration(const Configuration& src) { *this = src; }
Configuration&	Configuration::operator=( Configuration const & src )
{
	_ip_address = src.get_ip_address();
	_port = src.get_port();
	_max_clients = src.get_max_clients();
	_listen_sk = src.get_listen_sk();
	return (*this);
}
Configuration::~Configuration() {}
Configuration::Configuration(const char* ip, int port)
{
	_ip_address = (char *) ip;
	_port = port;
	_max_clients = 128;
	_listen_sk = -1;
}
char*			Configuration::get_ip_address(void) const {return (_ip_address);}
short unsigned int	Configuration::get_port(void) const {return (_port);}
int			Configuration::get_max_clients(void) const {return (_max_clients);}
int			Configuration::get_listen_sk(void) const {return (_listen_sk);}

void			Configuration::set_listen_sk(int i) {_listen_sk = i;}
