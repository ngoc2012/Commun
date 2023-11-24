/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 13:15:06 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "ClientRequest.hpp"

#include "Header.hpp"

Header::Header()
{
	std::cout << "Header Default constructor" << std::endl;
}
Header::Header(const Header& src) { *this = src; }
Header&	Header::operator=( Header const & src )
{
	(void) src;
	return (*this);
}
Header::Header(int sk, Host* h, Server* s, ClientRequest* r) :
_socket(sk),
_host(h),
_server(s),
_request(r)
{
	_locations = s->get_locations();
	std::cout << "Header Constructor sk: " << sk << std::endl;
}
Header::~Header()
{
	std::cout << "Destruction response" << std::endl;
}

std::vector<e_method>::iterator	Header::find_method(e_method m, std::vector<e_method> methods)
{
	std::vector<e_method>::iterator	it;
	for (it = methods.begin(); it != methods.end(); ++it)
		if (m == *it)
		{
			std::cout << _request->get_method() << "==" << *it << std::endl;
			return (it);
		}
	return (it);
}

bool	Header::find_url(std::string url, std::string l_url)
{
	std::cout << url << "==" << l_url << std::endl;
	if (url == l_url)
		return (true);
	if (url.length() > 1 && url.substr(0, l_url.length()) == l_url)
		return (true);
	return (false);
}

std::vector<Location*>::iterator	Header::find_location(std::string url)
{
	std::vector<Location*>::iterator it;
	for (it = _locations.begin(); it != _locations.end(); ++it)
	{
		std::vector<e_method>		methods = (*it)->get_methods();
		if (find_method(_request->get_method(), methods) != methods.end()
			&& find_url(url, (*it)->get_url()))
			return (it);
	}
	return (it);
}

void	Header::send(void)
{
	std::vector<Location*>::iterator it = find_location(_request->get_url());
	if (it != _locations.end())
		std::cout << "Found url: " << (*it)->get_url() << std::endl;

	//Send back data
	const char* http_response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n" 	// Close the connection after this response
		"\r\n"  			// End of headers
		"<link rel=\"icon\" href=\"data:,\">"
		"<html><body><h1>Hello, client!</h1></body></html>";
	if (::send(_socket, http_response, strlen(http_response), 0) < 0)
		perror("  send() failed");
	_host->close_client_sk(_socket);
	_host->delete_response(_socket);
	std::cout << "Header sent" << std::endl;
}
