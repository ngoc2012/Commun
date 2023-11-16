/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 17:55:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"
#include "Host.hpp"

ClientRequest::ClientRequest()
{
	std::cout << "ClientRequest Default constructor" << std::endl;
	clean();
}
ClientRequest::ClientRequest(const ClientRequest& src) { *this = src; }
ClientRequest&	ClientRequest::operator=( ClientRequest const & src )
{
	(void) src;
	return (*this);
}
ClientRequest::ClientRequest(int sk, Host* h) : _socket = sk, _host = h
{
	std::cout << "ClientRequest Constructor sk: " << sk << std::endl;
}
ClientRequest::~ClientRequest()
{
	std::cout << "Destruction client request" << std::endl;
	if (_socket > 0)
	{
		std::cout << "Close socket: " << _socket << std::endl;
		close(_socket);
	}
}

void	ClientRequest::clean()
{
	_socket = -1;
	_http_request = "";
	_method = "";
	_url = "";
}

void	ClientRequest::connect_client_sk(void)
{
	std::cout << "Socket " << _socket << " is readable." << std::endl;
	get_client_request(i);
	server_response(i);
	close_connection(i);
}

void	ClientRequest::set_method(std::string m) {_method = m;}
void	ClientRequest::set_http_request(std::string s) {_http_request = s;}
void	ClientRequest::cat_http_request(std::string s) {_http_request += s;}

std::string	ClientRequest::get_method(void) const {return (_method);}
std::string	ClientRequest::get_http_request(void) const {return (_http_request);}
