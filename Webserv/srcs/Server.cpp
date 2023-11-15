/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 21:35:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	_ip_address = std::string("127.0.0.1");
	_port = 4242;
	_listen_sk = -1;
}
Server::Server(const Server& src) { *this = src; }
Server&	Server::operator=( Server const & src )
{
	_ip_address = std::string(src.get_ip_address());
	_port = src.get_port();
	_listen_sk = src.get_listen_sk();
	return (*this);
}
Server::~Server() {}
Server::Server(const char* ip, int port)
{
	_ip_address = std::string(ip);
	_port = port;
	_listen_sk = -1;
}

void	Server::bind_addr(Server* c)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip_address.c_str());
	std::cout << "Listening at " << c->get_ip_address() << ":" << c->get_port() << std::endl;
	if (bind(c->get_listen_sk(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close_all_listen_sk();
		exit(-1);
	}
	if (listen(c->get_listen_sk(), _max_clients) < 0)
	{
		perror("listen() failed");
		close_all_listen_sk();
		exit(-1);
	}
}

const char*		Server::get_ip_address(void) const {return (_ip_address.c_str());}
short unsigned int	Server::get_port(void) const {return (_port);}
int			Server::get_listen_sk(void) const {return (_listen_sk);}

void			Server::set_listen_sk(int i) {_listen_sk = i;}
void			Server::set_ip_address(std::string ip) {_ip_address = ip;}
void			Server::set_port(short unsigned int p) {_port = p;}
