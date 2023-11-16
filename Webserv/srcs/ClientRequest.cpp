/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 14:40:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

ClientRequest::ClientRequest() { clean(); }
ClientRequest::ClientRequest(const ClientRequest& src) { *this = src; }
ClientRequest&	ClientRequest::operator=( ClientRequest const & src )
{
	(void) src;
	return (*this);
}
ClientRequest::~ClientRequest() {}

void	ClientRequest::clean()
{
	_socket = -1;
	_http_request = "";
	_method = "";
	_url = "";
}

void	ClientRequest::set_method(std::string m) {_method = m;}
void	ClientRequest::set_http_request(std::string s) {_http_request = s;}
void	ClientRequest::cat_http_request(std::string s) {_http_request += s;}

std::string	ClientRequest::get_method(void) const {return (_method);}
std::string	ClientRequest::get_http_request(void) const {return (_http_request);}
