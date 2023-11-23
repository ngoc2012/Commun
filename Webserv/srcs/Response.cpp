/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 10:27:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Response.hpp"

Response::Response()
{
	std::cout << "Response Default constructor" << std::endl;
	clean();
}
Response::Response(const Response& src) { *this = src; }
Response&	Response::operator=( Response const & src )
{
	(void) src;
	return (*this);
}
Response::Response(int sk, Host* h, Server* s) : _socket(sk), _host(h), _server(s)
{
	std::cout << "Response Constructor sk: " << sk << std::endl;
}
Response::~Response()
{
	std::cout << "Destruction client request" << std::endl;
	if (_socket > 0)
	{
		std::cout << "Close socket: " << _socket << std::endl;
		close(_socket);
	}
}
