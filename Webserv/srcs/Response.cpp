/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/25 20:05:47 by ngoc             ###   ########.fr       */
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
	_full_file_name = "";
	_status_code = 200;
	_location = 0;
	_end = false;
	std::cout << "Response Constructor sk: " << sk << std::endl;
}
Response::~Response()
{
	std::cout << "Destruction response" << std::endl;
}

bool	Response::find_method(e_method m, Location* loc)
{
	std::vector<e_method>	methods = loc->get_methods();

	for (std::vector<e_method>::iterator	it = methods.begin();
		it != methods.end(); ++it)
		if (m == *it)
		{
			std::cout << *it << std::endl;
			return (true);
		}
	//std::cout << _request->get_method() << "==" << *it << std::endl;
	return (false);
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
		if (compare_url(url, (*it)->get_url()))
		{
			if (find_method(_request->get_method(), *it))
				_location = *it;
			else
				_status_code = 405; // Method not allowed
			return ;
		}
	}
	_status_code = 404; // Not found
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

std::string	Response::get_file_extension(std::string& file_path)
{
	size_t dot_position = file_path.find_last_of('.');
	if (dot_position != std::string::npos && dot_position < file_path.size() - 1)
		return (file_path.substr(dot_position + 1));
	return ("");
}

void	Response::get_full_file_name(std::string url)
{
	if (_location)
	{
		if (_location->get_alias() == "")
			_full_file_name += _server->get_root();
		else
			_full_file_name += _location->get_alias();
		if (url.size() > _location->get_url().size())
			_full_file_name += url.substr(1, url.size() - 1);
	}
	struct stat	info;
	if (stat(_full_file_name.c_str(), &info) == 0 && S_ISDIR(info.st_mode))
		_full_file_name += "index.html";
	struct stat	buffer;
	if (stat(_full_file_name.c_str(), &buffer) != 0)
		_status_code = 404; // Not found
	std::cout << _full_file_name << std::endl;
}

void	Response::send(void)
{
	std::string	url = _request->get_url();

	find_location(url);
	if (_status_code == 200)
		get_full_file_name(url);
	Header	header(_status_code, get_file_extension(_full_file_name), this);
	header.set_allow(get_methods_str());
	switch (_request->get_method())
	{
		case GET:
			_body = get();
			_content_length = get_file_size(_full_file_name);
			break;
		default:
			_body = "<!doctype html>\n"
				"<link rel=\"icon\" href=\"data:,\">\n"
				"<html><body><h1>Hello, client!</h1></body></html>";
			_content_length = _body.length();
			break;
	}

	std::string	http_response = header.generate();
	http_response += _body;
	std::cout << http_response << std::endl;
	if (::send(_socket, http_response.c_str(), http_response.length(), 0) < 0)
		perror("  send() failed");
	if (_end)
	{
		_host->close_client_sk(_socket);
		_host->delete_response(_socket);
		std::cout << "Response sent" << std::endl;
	}
}

size_t		Response::get_file_size(std::string &file_name)
{
	std::ifstream file(file_name, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return 0;
	}
	return (file.tellg());
}

std::string	Response::get(void)
{ 

	return ("<!doctype html>\n"
		"<link rel=\"icon\" href=\"data:,\">\n"
		"<html><body><h1>Hello, client!</h1></body></html>");
}

Location*	Response::get_location(void) const {return (_location);}
size_t		Response::get_content_length(void) const {return (_content_length);}
