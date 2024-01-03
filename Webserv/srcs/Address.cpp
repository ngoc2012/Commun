/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/03 11:33:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void    Address::push(Server* s) { _servers.push_back(s); }

int	    Address::bind_addr(void)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip_address.c_str());
	if (bind(_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		return (-1);
	}
	if (listen(_socket, _host->get_max_clients()) < 0)
	{
		perror("listen() failed");
		return (-1);
	}
	std::cout << "Listening at " << _ip_address << ":" << _port
		<< " (socket : " << _socket << ")" << std::endl;
	return (_socket);
}
