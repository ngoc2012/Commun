/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/07 09:16:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Request.hpp"

Request::Request()
{
	std::cout << "Request Default constructor" << std::endl;
	clean();
}
Request::Request(const Request& src) { *this = src; }
Request&	Request::operator=( Request const & src )
{
	(void) src;
	return (*this);
}
Request::Request(int sk, Host* h, Server* s) : _socket(sk), _host(h), _server(s)
{
	_body_max = _host->get_client_max_body_size() * MEGABYTE;
	_body_buffer = _host->get_client_body_buffer_size() * KILOBYTE;
	_response.set_socket(sk);
	_response.set_host(h);
	_response.set_server(s);
	_response.set_request(this);
	//std::cout << _body_max << " " << _body_buffer << std::endl;
	clean();
	std::cout << "Request Constructor sk: " << sk << std::endl;
}
Request::~Request()
{
	std::cout << "Destruction client request" << std::endl;
	if (_socket > 0)
	{
		std::cout << "Close socket: " << _socket << std::endl;
		close(_socket);
	}
}

void	Request::clean()
{
	_body_in_header = "";
	_header = "";
	_body_size = 0;
	_content_type = "";
	_method = NONE;
	_url = "";
	_status_code = 200;
}

void	Request::read_header(void)
{
	//std::cout << "read_request" << std::endl;
	//clean();
    int ret = 1;
	while (_header.find("\r\n\r\n") == std::string::npos && ret > 0)
            ret = receive_data(_header);
	//std::cout << "_header\n" << _header << std::endl;
	if (_header.size() <= 0 || !parser_header())
	{
        if (_header.size() <= 0)
		    std::cerr << "Error: no header.\n" << std::endl;
        else
		    std::cerr << "Error: header invalid.\n" << std::endl;
		_status_code = 400;	// Bad Request
	}
	std::cout << "===============================" << std::endl;
	std::cout << "Header:\n" << _header << std::endl;
	std::cout << "===============================" << std::endl;
	std::cout << "Body:\n" << _body_in_header << std::endl;
	std::cout << "===============================" << std::endl;
	_response.set_status_code(_status_code);
	_host->new_response_sk(_socket);
}

int	Request::receive_data(std::string &data)
{
	char		request[_body_buffer + 1];

	int	ret = recv(_socket, request, _body_buffer, 0);
	if (ret <= 0)
		return (ret);
	request[ret] = 0;
    //std::cout << request << std::endl;
	data += request;
	return (ret);
}

bool	Request::parser_header(void)
{
	std::vector<std::string>	lines = split_string(_header, "\n");
	std::vector<std::string>	first_line = split_string(lines[0], " 	");
    //std::cout << first_line.size() << std::endl;
	if (first_line.size() < 3 || !read_method(first_line[0]))
		return (false);
	_url = first_line[1];
    read_content_type(_header, _content_type);
	if (!split_header_body(_header))
		return (false);
	return (true);
}

bool	Request::read_method(std::string& s)
{
	//std::cout << s << std::endl;
	if (s == "GET")
		_method = GET;
	else if (s == "POST")
		_method = POST;
	else if (s == "PUT")
		_method = POST;
	else
	{
		std::cerr << "Error: Method unknown : " << s << std::endl;
		return (false);
	}
	return (true);
}

bool	Request::split_header_body(std::string& s)
{
	size_t  pos = s.find("\r\n\r\n");
    if (pos != std::string::npos)
    {
        //std::cout << pos << std::endl;
	    _body_in_header = s.substr(pos + 2, _header.size() - pos - 2);
    	_header = s.substr(0, pos);
	    return (true);
    }
    return (false);
}

bool	Request::read_content_type(std::string& s, std::string& c)
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
            {
			    c = words[0];
		        return (true);
            }
        std::cerr << "Error: Content type not found." << std::endl;
	    return (false);
	}
    std::cerr << "Error: Content type not found." << std::endl;
	return (false);
}

e_method	Request::get_method(void) const {return (_method);}
std::string	Request::get_url(void) const {return (_url);}
Response*	Request::get_response(void) {return (&_response);}
int		    Request::get_status_code(void) const {return (_status_code);}
std::string	Request::get_body_in_header(void) const {return (_body_in_header);}
size_t		Request::get_body_buffer(void) const {return (_body_buffer);}
