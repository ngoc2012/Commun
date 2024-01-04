/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/04 10:45:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
//#include "Request.hpp"
//#include "Response.hpp"
#include "webserv.hpp"

#include "Address.hpp"

Address::Address()
{
	std::cout << "Address Default constructor" << std::endl;
}
Address::Address(const Address& src) { *this = src; }
Address&	Address::operator=( Address const & src )
{
	(void) src;
	return (*this);
}
Address::~Address()
{
	std::cout << "Address Destructor" << std::endl;
	for (std::vector<Server*>::iterator it = _servers.begin();
		it != _servers.end(); ++it)
		delete (*it);
}
Address::Address(std::string ip, short unsigned int p): _ip_address(ip), _port(p) {}

void    Address::push(Server* s) { _servers.push_back(s); }

int     Address::listen_socket(Host* host)
{
    int     s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		perror("listen socket: socket() failed");
		return (-1);
	}
	int    on = 1;
	if (setsockopt(s, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		return (-1);
	}
	fcntl(s, F_SETFL, O_NONBLOCK);	// ioctl not allowed
	return (bind_addr(host, s));
}

int	    Address::bind_addr(Host* host, int socket)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip_address.c_str());
	if (bind(socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		return (-1);
	}
	if (listen(socket, host->get_max_clients()) < 0)
	{
		perror("listen() failed");
		return (-1);
	}
	std::cout << "Listening at " << _ip_address << ":" << _port
		<< " (socket : " << socket << ")" << std::endl;
	return (socket);
}

//Accept all the new connections, create a new socket and add to the master set
void	Address::accept_client_sk(void)
{
	std::cout << "Listening socket is readable " << _socket << std::endl;
	int	new_sk;
	do
	{
		new_sk = accept(_socket, NULL, NULL);
		if (new_sk < 0)
		{
			if (errno != EWOULDBLOCK)
				perror("accept() failed");
			break;
		}
		fcntl(new_sk, F_SETFL, O_NONBLOCK);
		std::cout << "  New incoming connection - " << new_sk << std::endl;
		_host->new_request_sk(new_sk, this);
	} while (new_sk != -1);
}
