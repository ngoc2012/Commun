/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 21:59:14 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "ClientRequest.hpp"
#include "Header.hpp"

#include "Response.hpp"

Response::Response()
{
	std::cout << "Response Default constructor" << std::endl;
}
Response::Response(const Response& src) { *this = src; }
Response&	Response::operator=( Response const & src )
{
	(void) src;
	return (*this);
}
Response::Response(int sk, Host* h, Server* s, ClientRequest* r) :
_socket(sk),
_host(h),
_server(s),
_request(r)
{
	_location = 0;
	std::cout << "Response Constructor sk: " << sk << std::endl;
}
Response::~Response()
{
	std::cout << "Destruction response" << std::endl;
}

std::vector<e_method>::iterator	Response::find_method(e_method m, std::vector<e_method> methods)
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

bool	Response::find_url(std::string url, std::string l_url)
{
	std::cout << url << "==" << l_url << std::endl;
	if (url == l_url)
		return (true);
	if (url.length() > 1 && url.substr(0, l_url.length()) == l_url)
		return (true);
	return (false);
}

void	Response::find_location(std::string url)
{
	std::vector<Location*>		locations = _server->get_locations();
	std::vector<Location*>::iterator it;
	for (it = locations.begin(); it != locations.end(); ++it)
	{
		std::vector<e_method>		methods = (*it)->get_methods();
		if (find_method(_request->get_method(), methods) != methods.end()
			&& find_url(url, (*it)->get_url()))
			_location = *it;
	}
}

void	Response::send(void)
{
	find_location(_request->get_url());
	if (_location)
		std::cout << "Found url: " << _location->get_url() << std::endl;
	//Send back data
	Header	header(200, std::string("default"), this);
	header.set_allow(get_methods_str());
	std::string	http_response = header.generate();
	std::string	body = "<link rel=\"icon\" href=\"data:,\">"
		"<html><body><h1>Hello, client!</h1></body></html>";
	_content_length = body.length();
	http_response += body;
	//const char* http_response =
	//	"HTTP/1.1 200 OK\r\n"
	//	"Content-Type: text/html\r\n"
	//	"Connection: close\r\n" 	// Close the connection after this response
	//	"\r\n"  			// End of headers
	if (::send(_socket, http_response.c_str(), http_response.length(), 0) < 0)
		perror("  send() failed");
	_host->close_client_sk(_socket);
	_host->delete_response(_socket);
	std::cout << "Response sent" << std::endl;
}

std::string	Response::get_methods_str(void)
{
}

Location*	Response::get_location(void) const {return (_location);}
size_t		Response::get_content_length(void) const {return (_content_length);}
