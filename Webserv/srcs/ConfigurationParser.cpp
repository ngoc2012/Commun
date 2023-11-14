/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 09:49:14 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigurationParser.hpp"

ConfigurationParser::ConfigurationParser() {}
ConfigurationParser::ConfigurationParser(const ConfigurationParser& src) { *this = src; }
ConfigurationParser&	ConfigurationParser::operator=( ConfigurationParser const & src )
{
	_ip_address = src.get_ip_address();
	_port = src.get_port();
	_max_clients = src.get_max_clients();
	_listen_sk = src.get_listen_sk();
	return (*this);
}
ConfigurationParser::~ConfigurationParser() {}
ConfigurationParser::ConfigurationParser(const char* ip, int port)
{
	_ip_address = (char *) ip;
	_port = port;
	_max_clients = 128;
	_listen_sk = -1;
}
char*			ConfigurationParser::get_ip_address(void) const {return (_ip_address);}
short unsigned int	ConfigurationParser::get_port(void) const {return (_port);}
int			ConfigurationParser::get_max_clients(void) const {return (_max_clients);}
int			ConfigurationParser::get_listen_sk(void) const {return (_listen_sk);}

void			ConfigurationParser::set_listen_sk(int i) {_listen_sk = i;}
