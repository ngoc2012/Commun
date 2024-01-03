/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/03 11:27:57 by ngoc             ###   ########.fr       */
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

void    Address::push(Server*)
{
}
