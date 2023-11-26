/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/26 13:56:09 by ngoc             ###   ########.fr       */
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
	_header = "";
	_full_file_name = "";
	_status_code = 200;
	_location = 0;
	_end = false;
	std::cout << "Response Constructor sk: " << sk << std::endl;
}
Response::~Response()
{
	if (_file.is_open())
	{
		std::cout << "File in response close" << std::endl;
		_file.close();
		if (_file.fail())
			std::cerr << "Error closing file" << std::endl;
		else
			std::cout << "File closed successfully" << std::endl;
	}
	std::cout << "Destruction response" << std::endl;
}

bool	Response::find_method(e_method m, Location* loc)
{
	std::vector<e_method>	methods = loc->get_methods();

	for (std::vector<e_method>::iterator	it = methods.begin();
		it != methods.end(); ++it)
		if (m == *it)
			return (true);
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
			|| (url.size() > l_url.size() && url.substr(0, l_url.size()) == l_url))
			return (true);
	}
	// File
	else if (url == l_url)
		return (true);
	return (false);
}

void	Response::find_location(std::string url)
{
	bool	found = false;

	std::vector<Location*>		locations = _server->get_locations();
	for (std::vector<Location*>::iterator it = locations.begin();
		it != locations.end(); ++it)
	{
		if (compare_url(url, (*it)->get_url()))
		{
			_location = *it;
			found = true;
			if (find_method(_request->get_method(), *it))
				_status_code = 200;
			else
				_status_code = 405; // Method not allowed
		}
	}
	if (!found)
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
	if (_header == "")
	{
		std::string	url = _request->get_url();
		find_location(url);
		if (_status_code == 200)
			get_full_file_name(url);
		Header	header(_status_code, get_file_extension(_full_file_name), this);
		header.set_allow(get_methods_str());
		if (_status_code == 200)
		{
			std::cout << _full_file_name << std::endl;
			switch (_request->get_method())
			{
				case GET:
					_content_length = get_file_size(_full_file_name);
					//_content_length = 2 * _host->get_client_body_buffer_size() * KILOBYTE;
					std::cout << "File open" << std::endl;
					_file.open(_full_file_name.c_str(), std::ios::binary);
					if (!_file.is_open())
					{
						std::cerr << "Failed to open file: " << _full_file_name << std::endl;
						_status_code = 500;	// Internal server error
						_end = true;
					}
					break;
				default:
					_body = "<!doctype html>\n"
						"<link rel=\"icon\" href=\"data:,\">\n"
						"<html><body><h1>Hello, client!</h1></body></html>";
					_content_length = _body.length();
					break;
			}
		}
		else
			_end = true;

		_header = header.generate();
		std::cout << "Header:\n" << _header << std::endl;
		if (::send(_socket, _header.c_str(), _header.length(), 0) < 0)
		{
			_end = true;
			perror("send() failed");
		}
	}
	else if (_request->get_method() == GET)
	{
		//std::cout << "Get more" << std::endl;
		get();
	}
	if (_end)
	{
	      _host->close_client_sk(_socket);
	      _host->delete_response(_socket);
	      std::cout << "Response sent" << std::endl;
	}
}

size_t		Response::get_file_size(std::string &file_name)
{
	std::ifstream file(file_name.c_str(), std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		_status_code = 500;	// Internal server error
		return 0;
	}
	return (file.tellg());
}

void	Response::get(void)
{ 
	size_t	chunk_size = _host->get_client_body_buffer_size() * KILOBYTE;

	char	buffer[chunk_size];
	std::cout << "chunk_size:\n" << chunk_size << std::endl;
	_file.read(buffer, chunk_size);
	size_t	bytes_read = _file.gcount();
	::send(_socket, buffer, bytes_read, 0);
	if (_file.eof())
	{
		_file.close();
		_end = true;
	}
}

Location*	Response::get_location(void) const {return (_location);}
size_t		Response::get_content_length(void) const {return (_content_length);}
