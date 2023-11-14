/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 22:25:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	_ip_address = std::string("127.0.0.1");
	_port = 4242;
	_max_clients = 128;
	_listen_sk = -1;
}
Server::Server(const Server& src) { *this = src; }
Server&	Server::operator=( Server const & src )
{
	_ip_address = std::string(src.get_ip_address());
	_port = src.get_port();
	_max_clients = src.get_max_clients();
	_listen_sk = src.get_listen_sk();
	return (*this);
}
Server::~Server() {}
Server::Server(const char* ip, int port)
{
	_ip_address = std::string(ip);
	_port = port;
	_max_clients = 128;
	_listen_sk = -1;
}
const char*		Server::get_ip_address(void) const {return (_ip_address.c_str());}
short unsigned int	Server::get_port(void) const {return (_port);}
int			Server::get_max_clients(void) const {return (_max_clients);}
int			Server::get_listen_sk(void) const {return (_listen_sk);}

void			Server::set_listen_sk(int i) {_listen_sk = i;}
void			Server::set_ip_address(std::string ip) {_ip_address = ip;}
