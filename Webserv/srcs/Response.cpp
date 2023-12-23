/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/23 08:29:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Request.hpp"
#include "Header.hpp"

#include "Response.hpp"

Response::Response()
{
    std::cout << "Response Default constructor" << std::endl;
    _header = "";
    _status_code = 200;
    _content_length = 0;

    _full_file_name = "";
    _write_queue = false;
    _fd_out = -1;
    _end_fd_out = false;
}
Response::Response(const Response& src) { *this = src; }
Response&	Response::operator=( Response const & src )
{
	(void) src;
	return (*this);
}
Response::~Response()
{
    if (_fd_out > 0)
        close(_fd_out);
	//std::cout << "Destruction response: " << _socket << std::endl;
}

int     Response::write()
{
    if (!_write_queue)
        return (0);
    if (_header == "")
    {
        write_header();
        if (_status_code != 200)
            return (end_connection());
        get_fd_out();
        if (_status_code != 200)
            return (end_connection());
    }
    else
        write_body();
    return (0);
}

void     Response::write_header()
{
    //std::cout << "write_header" << std::endl;

    _full_file_name = _request->get_full_file_name();
    Header	header(this, ft::file_extension(_full_file_name));
    header.set_allow(_request->get_location()->get_methods_str());
    if (_status_code == 200 && _request->get_method() == GET)
        get_file_size();
    _header = header.generate();
    std::cout << "Header:\n" << _header << std::endl;
    if (send(_socket, _header.c_str(), _header.length(), 0) < 0)
        end_connection();
}

void     Response::get_file_size()
{
    _fd_out = open(_full_file_name.c_str(), O_RDONLY);
    if (_fd_out == -1)
    {
        std::cerr << "Error: Can not open file " << _full_file_name << std::endl;
        _status_code = 500;
        return ;
    }
    struct stat fileStat;
    if (stat(_full_file_name.c_str(), &fileStat) == 0)
        _content_length = fileStat.st_size;
    else
    {
        std::cerr << "Error: Get file size." << std::endl;
        _status_code = 500;
        return ;
    }
}

void     Response::get_fd_out()
{
    std::cout << _full_file_name << std::endl;
    switch (_request->get_method())
    {
        case GET:
            _fd_out = open(_full_file_name.c_str(), O_RDONLY);
            if (_fd_out == -1)
                _status_code = 500;
            break;
        default:
            end_connection();
            break;
    }
}

void     Response::write_body()
{
    _write_queue = true;

	char	buffer[RESPONSE_BUFFER];
	int ret = read(_fd_out, buffer, RESPONSE_BUFFER);

	if (send(_socket, buffer, ret, 0) < 0)
        end_connection();
}

int     Response::end_connection(void)
{
    if (_fd_out > 0)
        close(_fd_out);
    _write_queue = false;
    _end_fd_out = true;
    return (0);
}

int		    Response::get_status_code(void) const {return (_status_code);}
bool		Response::get_end_fd_out(void) const {return (_end_fd_out);}
size_t		Response::get_content_length(void) const {return (_content_length);}

void		Response::set_socket(int s) {_socket = s;}
void		Response::set_host(Host* h) {_host = h;}
void		Response::set_server(Server* s) {_server = s;}
void		Response::set_request(Request* r) {_request = r;}
void		Response::set_status_code(int e) {_status_code = e;}
void        Response::set_write_queue(bool b) {_write_queue = b;}

//size_t		Response::get_file_size(std::string &file_name)
//{
//	std::ifstream file(file_name.c_str(), std::ios::binary | std::ios::ate);
//	if (!file.is_open()) {
//		std::cerr << "Failed to open file: " << file_name << std::endl;
//		_status_code = 500;	// Internal server error
//		return 0;
//	}
//	return (file.tellg());
//}
