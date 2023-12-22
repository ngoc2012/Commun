/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/22 11:47:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Location.hpp"

Request::Request()
{
	std::cout << "Request Default constructor" << std::endl;
}
Request::Request(const Request& src) { *this = src; }
Request&	Request::operator=( Request const & src )
{
	(void) src;
	return (*this);
}
Request::Request(int sk, Host* h, Server* s) : _socket(sk), _host(h), _server(s)
{
	std::cout << "Request Constructor sk: " << sk << std::endl;

	_response.set_socket(sk);
	_response.set_host(h);
	_response.set_server(s);
	_response.set_request(this);

	_header = "";
	_url = "";
	_method = NONE;
	_content_type = "";
	_body_size = 0;

	_fd_in = -1;
	_full_file_name = "";
    _body_max = _host->get_client_max_body_size() * MEGABYTE;
    _body_buffer = _host->get_client_body_buffer_size() * KILOBYTE;
    _buffer = new char[_body_buffer + 1];
	_read_queue = true;
    _end_fd_in = false;

	_status_code = 200;
}

Request::~Request()
{
	std::cout << "Destruction client request" << std::endl;

    delete[] _buffer;
	if (_socket > 0)
	{
		std::cout << "Close socket: " << _socket << std::endl;
		close(_socket);
	}
}

int     Request::read(void)
{
    if (!_read_queue)
        return (0);
    if (_header == "")
    {
        read_header();
        if (_status_code != 200)
            return (end_read());
        get_fd_in();
        if (_status_code != 200)
            return (end_read());
    }
    else
        read_body();
    return (0);
}

void	Request::read_header()
{
    int ret = 1;

    _body_position = NPOS;
	while (_body_position == NPOS && ret > 0)
    {
        ret = recv(_socket, _buffer, _body_buffer, 0);
        if (ret < 0)
        {
            _status_code = 500;
            return ;
        }
        if (ret > 0)
        {
            _buffer[ret] = 0;
            _header += _buffer;
            _body_position = _header.find("\r\n\r\n");
        }
    }
	//std::cout << "_header" << _header.size() << std::endl << _header << std::endl;
	if (_body_position == NPOS)
    {
        std::cerr << "Error: No end header found.\n" << std::endl;
		_status_code = 400;	// Bad Request
        return ;
    }
    _body_position += 4;
    _body_size = ret - _body_position;
	if (!parser_header())
	{
        std::cerr << "Error: request header invalid.\n" << std::endl;
		_status_code = 400;	// Bad Request
        return ;
	}
    else
    {
        std::cout << "============================" << std::endl;
        std::cout << "Header:" << _header.size() << std::endl  << _header << std::endl;
        std::cout << "============================" << std::endl;
        check_location();
    }
}

bool	Request::parser_header(void)
{
	if (!read_method_url())
		return (false);
    if (_method != GET && !read_content_type(_header, _content_type))
    {
        std::cerr << "Error: Content type unknown" << std::endl;
		return (false);
    }
	return (true);
}

bool	Request::read_method_url()
{
    size_t  newline = _header.find("\n");
    if (newline == NPOS)
        return (false);

    std::vector<std::string>	line0;
    line0 = split_string(_header.substr(0, newline), "     ");
    if (line0.size() != 3)
    {
        std::cerr << "Error: First line header" << std::endl;
        return (false);
    }
    _url = line0[1];
    if (line0[0] == "GET")
        _method = GET;
    else if (line0[0] == "POST")
        _method = POST;
    else if (line0[0] == "PUT")
        _method = PUT;
    else
    {
        std::cerr << "Error: Method unknown : " << line0[0] << std::endl;
        return (false);
    }
    return (true);
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
	if (pos != NPOS)
	{
		for (int i = 0; i < 18; i++)
			if (s.substr(pos + 14, 50).find(types[i]) != NPOS)
            {
			    c = types[i];
		        return (true);
            }
        std::cerr << "Error: Content type not found." << std::endl;
	    return (false);
	}
    std::cerr << "Error: Content type not found." << std::endl;
	return (false);
}

void	Request::read_body()
{
    char	buffer[_body_buffer];
    int     ret;

	//std::cout << "chunk_size: " << chunk_size << std::endl;
    ret = recv(_socket, buffer, _body_buffer, 0);
    if (ret < 0)
    {
        std::cerr << "Error: recv error" << std::endl;
        _status_code = 400;
        end_read();
        return ;
    }
    if (ret == 0)
        end_read();
    if (ret > 0 && _fd_in > 0)
        write(_fd_in, buffer, ret);
}

void	Request::check_location()
{
    _location = Location::find_location(_url,
            _server->get_locations(), _method, _status_code);

    if (!_location || _status_code != 200)
        return ;

    _full_file_name = _location->get_full_file_name(_url,
            _server->get_root());

	struct stat buffer;
	if (_method != PUT
            && stat(_full_file_name.c_str(), &buffer) != 0)
		_status_code = 404; // Not found
}

void	Request::get_fd_in()
{
    switch (_method)
    {
        case GET:
            break;
        case PUT:
            _fd_in = open(_full_file_name.c_str(),
                    O_CREAT | O_WRONLY | O_APPEND, 0664);
            if (_fd_in == -1)
                _status_code = 500;
            break;
        case POST:
            break;
        case NONE:
            break;
    }
    if (_body_size > 0 && _fd_in != -1)
        write(_fd_in, &_buffer[_body_position], _body_size);
}

int     Request::end_read(void)
{
    if (_fd_in > 0)
        close(_fd_in);
    _read_queue = false;
    _end_fd_in = true;
    _host->new_response_sk(_socket);
    _response.set_status_code(_status_code);
    _response.set_write_queue(true);
    return (0);
}

bool        Request::get_end_fd_in(void) const {return (_end_fd_in);}
e_method	Request::get_method(void) const {return (_method);}
std::string	Request::get_url(void) const {return (_url);}
Response*	Request::get_response(void) {return (&_response);}
int		    Request::get_status_code(void) const {return (_status_code);}
std::string	Request::get_content_type(void) const {return (_content_type);}
size_t		Request::get_body_size(void) const {return (_body_size);}
std::string	Request::get_header(void) const {return (_header);}
std::string	Request::get_full_file_name(void) const {return (_full_file_name);}
