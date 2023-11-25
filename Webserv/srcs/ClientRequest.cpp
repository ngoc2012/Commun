/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/25 09:08:36 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "ClientRequest.hpp"

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
ClientRequest::ClientRequest(int sk, Host* h, Server* s) : _socket(sk), _host(h), _server(s)
{
	_body_max = _host->get_client_max_body_size() * MEGABYTE;
	_body_buffer = _host->get_client_body_buffer_size() * KILOBYTE;
	std::cout << _body_max << " " << _body_buffer << std::endl;
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
	_body = "";
	_header = "";
	_body_size = 0;
	_content_type0 = "";
	_content_type1 = "";
	_method = NONE;
	_url = "";
	_end = false;
}

int	ClientRequest::read_error(std::string s, int err_code)
{
	(void) err_code;
	std::cerr << s << std::endl;
	_host->new_response_sk(_socket, _server, this);
	return (err_code);
}

int	ClientRequest::read_client_request(void)
{
	std::cout << "read_client_request\n" << std::endl;
	//clean();
	if (_header == "")
	{
		receive_data(_header);
		if (!parser_header())
			return (read_error("Error: header invalid: \n" + _header, 401));
	}
	else
		receive_data(_body);
	if (_end)
		_host->new_response_sk(_socket, _server, this);
	//if (!read_body())
	//	return (read_error("Error: body invalid: \n" + _body, 401));
	//std::cout << "===============================" << std::endl;
	//std::cout << "Header:\n" << _header << std::endl;
	//std::cout << "===============================" << std::endl;
	//std::cout << "Body:\n" << _body << std::endl;
	//std::cout << "===============================" << std::endl;
	return (1);
}

int	ClientRequest::receive_data(std::string &data)
{
	//std::cout << "Receive data from client" << std::endl;
	char		response[_body_buffer + 1];

	int	ret = recv(_socket, response, _body_buffer, 0);
	if (ret < _body_buffer)
		_end = true;
	if (ret <= 0)
		return (0);
	data += response[ret];
	return (ret);
}

bool	ClientRequest::parser_header(void)
{

	std::vector<std::string>	lines = split_string(_header, "\n");
	std::vector<std::string>	first_line = split_string(lines[0], " 	");

	if (!read_method(first_line[0]))
		return (false);
	_url = first_line[1];
	read_content_type(_header, _content_type0);
	if (_content_type0 != "")
	{
		std::string s = _header.substr( _header.find("Content-Type:") + 14);
		read_content_type(s, _content_type1);
	}
	if (!find_start_body(_header))
		return (false);
	return (true);
}

bool	ClientRequest::read_method(std::string& s)
{
	//std::cout << s << std::endl;
	if (s == "GET")
		_method = GET;
	else if (s == "POST")
		_method = POST;
	else
	{
		std::cerr << "Error: Method unknown : " << s << std::endl;
		return (false);
	}
	return (true);
}

bool	ClientRequest::find_start_body(std::string& s)
{
	size_t	start = 0;
	size_t	pos0 = s.find("Content-Type:");
	if (pos0 != std::string::npos)
	{
		size_t	pos1 = s.find("Content-Type:", pos0 + 14);
		if (pos1 != std::string::npos)
		{
			pos0 = s.find("\r\n\r\n", pos1);
			if (pos0 != std::string::npos)
				start = pos0 + 4;
			else
				return (false);
		}
		else
		{
			pos1 = s.find("\r\n\r\n", pos0);
			if (pos1 != std::string::npos)
				start = pos1 + 4;
			else
				return (false);
		}
	}
	else
	{
		pos0 = s.find("\r\n\r\n");
		if (pos0 != std::string::npos)
			start = pos0 + 4;
	}
	_body = _header.substr(start, _header.length() - start);
	_header = _header.substr(0, start);
	return (true);
}

bool	ClientRequest::read_content_type(std::string& s, std::string& c)
{
	const char*	types[] = {
		"text/plain",
		"text/html",
		"text/css",
		"text/javascript",
		"text/xml",
		"application/json",
		"application/xml",
		"application/pdf",
		"application/zip",
		"application/octet-stream",
		"image/jpeg",
		"image/png",
		"image/gif",
		"image/svg+xml",
		"audio/mpeg",
		"video/mp4",
		"multipart/form-data",
		"application/x-www-form-urlencoded"
	};
	size_t	pos = s.find("Content-Type:");
	std::vector<std::string>	words;
	if (pos != std::string::npos)
	{
		words = split_string(s.substr(pos + 14, 50), ";\n");
		//std::cout << "|" << words[0] << "|" << std::endl << std::flush;
		for (int i = 0; i < 18; i++)
			if (words[0] == std::string(types[i]))
				c = words[0];
		return (false);
	}
	return (true);
}

e_method	ClientRequest::get_method(void) const {return (_method);}
std::string	ClientRequest::get_url(void) const {return (_url);}
