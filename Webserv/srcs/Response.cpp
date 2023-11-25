/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/25 15:01:08 by ngoc             ###   ########.fr       */
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
			return (it);
	//std::cout << _request->get_method() << "==" << *it << std::endl;
	return (it);
}

bool	Response::compare_url(std::string url, std::string l_url)
{
	//std::cout << url << "==" << l_url << std::endl;
	// Folder
	if (l_url[l_url.size() - 1] == '/')
	{
		if (url == l_url || url == l_url.substr(0, l_url.size() - 1)
			|| (l_url.size() > 1 && url.substr(0, l_url.size()) == l_url))
			return (true);
	}
	// File
	else if (url == l_url)
		return (true);
	return (false);
}

void	Response::find_location(std::string url)
{
	std::vector<Location*>		locations = _server->get_locations();
	for (std::vector<Location*>::iterator it = locations.begin();
		it != locations.end(); ++it)
	{
		std::vector<e_method>		methods = (*it)->get_methods();
		if ((find_method(_request->get_method(), methods) != methods.end())
			&& compare_url(url, (*it)->get_url()))
		{
			std::cout << "FOUND" << std::endl;
			_location = *it;
			return ;
		}
	}
}

std::string	Response::get_methods_str(void)
{
	if (!_location)
		return (std::string(""));
	std::vector<e_method>	methods = _location->get_methods();
	std::string	s = "";
	for(std::vector<e_method>::iterator it = methods.begin(); it != methods.end(); ++it)
	{
		if (it != methods.begin())
			s += ",";
		switch (*it)
		{
			case GET:
				s += "GET";
				break;
			case POST:
				s += "POST";
				break;
			case PUT:
				s += "PUT";
				break;
			case NONE:
				s += "NONE";
				break;
		}
	}
	return (s);
}

void	Response::send(void)
{
	find_location(_request->get_url());
	if (_location)
		std::cout << "Found url: " << _location->get_url() << std::endl;
	//Send back data
	Header	header(200, std::string("html"), this);
	header.set_allow(get_methods_str());
	std::string	body = "<!doctype html>\n"
		"<link rel=\"icon\" href=\"data:,\">\n"
		"<html><body><h1>Hello, client!</h1></body></html>";
	_content_length = body.length();

	std::string	http_response = header.generate();
	http_response += body;
	//const char* http_response =
	//	"HTTP/1.1 200 OK\r\n"
	//	"Content-Type: text/html\r\n"
	//	"Connection: close\r\n" 	// Close the connection after this response
	//	"\r\n"  			// End of headers
	std::cout << http_response << std::endl;
	if (::send(_socket, http_response.c_str(), http_response.length(), 0) < 0)
		perror("  send() failed");
	_host->close_client_sk(_socket);
	_host->delete_response(_socket);
	std::cout << "Response sent" << std::endl;
}

Location*	Response::get_location(void) const {return (_location);}
size_t		Response::get_content_length(void) const {return (_content_length);}
