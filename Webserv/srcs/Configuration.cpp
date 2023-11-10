/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/09 21:46:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

ClientRequest::ClientRequest()
{
	clean();
}
ClientRequest::ClientRequest(const ClientRequest& src) { *this = src; }
ClientRequest&	ClientRequest::operator=( ClientRequest const & src )
{
	(void) src;
	return (*this);
}
ClientRequest::~ClientRequest() {}
void	ClientRequest::clean()
{
	_http_request = "";
	_method = "";
	_url = "";
}
std::string	ClientRequest::get_http_request(void) {return (_http_request);}
void	ClientRequest::set_http_request(std::string s) {_http_request = s;}
