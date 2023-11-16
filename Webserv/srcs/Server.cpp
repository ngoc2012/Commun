/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 10:26:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	_ip_address = std::string("127.0.0.1");
	_port = 4242;
	_listen_sk = -1;
	_host = 0;
}
Server::Server(const Server& src) { *this = src; }
Server&	Server::operator=( Server const & src )
{
	_ip_address = std::string(src.get_ip_address());
	_port = src.get_port();
	_listen_sk = src.get_listen_sk();
	_host = src.get_host();
	return (*this);
}
Server::~Server()
{
	if (_listen_sk > 0)
		close(_listen_sk);
}

int	Server::new_listen_sk(void)
{
	_listen_sk = socket(AF_INET, SOCK_STREAM, 0);
	if (_listen_sk < 0)
	{
		perror("listen socket: socket() failed");
		return (-1);
	}
	int    on = 1;
	if (setsockopt(_listen_sk, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		return (-1);
	}
	fcntl(_listen_sk, F_SETFL, O_NONBLOCK);	// ioctl not allowed
	return (bind_addr());
}

int	Server::bind_addr(void)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip_address.c_str());
	if (bind(_listen_sk, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		return (-1);
	}
	if (listen(_listen_sk, _host->get_max_clients()) < 0)
	{
		perror("listen() failed");
		return (-1);
	}
	std::cout << "Listening at " << _ip_address << ":" << _port << std::endl;
	return (_listen_sk);
}

const char*		Server::get_ip_address(void) const {return (_ip_address.c_str());}
short unsigned int	Server::get_port(void) const {return (_port);}
int			Server::get_listen_sk(void) const {return (_listen_sk);}
Host*			Server::get_host(void) const {return (_host);}

void			Server::set_listen_sk(int i) {_listen_sk = i;}
void			Server::set_ip_address(std::string ip) {_ip_address = ip;}
void			Server::set_port(short unsigned int p) {_port = p;}
void			Server::set_host(Host* h) {_host = h;}
