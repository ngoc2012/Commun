/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 15:52:36 by ngoc             ###   ########.fr       */
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
	_content_type0 = "";
	_content_type1 = "";
	_method = NONE;
	_url = "";
}

int	ClientRequest::read_error(std::string s, int err_code)
{
	std::cerr << s << std::endl;
	_host->get_sk_server()[_socket]->response(_socket, err_code);
	_host->close_client_sk(_socket);
	return (err_code);
}

int	ClientRequest::read_client_request(void)
{
	if (!read_header())
		return (read_error("Error: can not receive client request", 401));
	if (!parser_header())
		return (read_error("Error: header invalid: \n" + _header, 401));
	if (!read_body())
		return (read_error("Error: body invalid: \n" + _body, 401));
	std::cout << "===============================" << std::endl;
	std::cout << "Header:\n" << _header << std::endl;
	std::cout << "===============================" << std::endl;
	std::cout << "Body:\n" << _body << std::endl;
	std::cout << "===============================" << std::endl;
	_host->new_response_sk(_socket, _server, this);
	return (1);
}

bool	ClientRequest::read_header(void)
{
	//std::cout << "Receive data from client" << std::endl;
	clean();
	char		response[BUFFER + 1];

	int	ret = recv(_socket, response, BUFFER, 0);
	if (ret <= 0)
		return (false);
	response[ret] = 0;
	_header	= std::string(response);
	//std::cout << "Read header:\n" << _header << std::endl;
	//std::cout << "===============================" << std::endl;
	return (true);
}

bool	ClientRequest::parser_header(void)
{

	std::vector<std::string>	lines = split_string(_header, "\n");
	std::vector<std::string>	first_line = split_string(lines[0], " 	");

	if (!read_method(first_line[0]))
		return (false);
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

bool	ClientRequest::read_body(void)
{
	int	ret = 1;
	char	response[BUFFER + 1];
	do
	{
		ret = recv(_socket, response, BUFFER, 0);
		if (ret > 0)
		{
			response[ret] = 0;
			_body += std::string(response);
		}
	} while (ret > 0);
	//std::cout << "Connection closed" << std::endl;
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
