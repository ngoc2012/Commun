/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 21:57:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "ClientRequest.hpp"
#include "Response.hpp"

#include "webserv.hpp"

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
Header::Header(int e, std::string extension, Response* r)
{
	_err_code = e;
	_response = r;
	init();
	std::cout << "Header Constructor" << std::endl;
}
std::string	Header::generate(void)
{
	std::string	str;

	str = "HTTP/1.1 ";
	str += itos(e) + " ";
	if (_status.find(e) == _status.end())
		str += "Unknown error code";
	else
		str += _status[e];
	str += "\r\n";
	str += "Allow: " + _allow + "\r\n";
	str += "Content-Language: en" + "\r\n";
	str += "Content-Length: " + _response->get_content_length() + "\r\n";
	if (_types.find(extension) == _types.end())
		str += "Content-Type: text/plain\r\n";
	else
		str += "Content-Type: " + _types[extension] + "\r\n";
	return (str);
}

void	Header::init(void)
{
	_status[100] = "Continue";
	_status[200] = "OK";
	_status[201] = "Created";
	_status[204] = "No Content";
	_status[400] = "Bad Request";
	_status[403] = "Forbidden";
	_status[404] = "Not Found";
	_status[405] = "Method Not Allowed";
	_status[413] = "Payload Too Large";
	_status[500] = "Internal Server Error";
	_types["html"] = "text/html";
	_types["css"] = "text/css";
	_types["js"] = "text/javascript";
	_types["jpeg"] = "image/jpeg";
	_types["jpg"] = "image/jpeg";
	_types["png"] = "image/png";
	_types["bmp"] = "image/bmp";
}


Header::~Header()
{
	std::cout << "Header Destruction" << std::endl;
}

std::string	Header::get_allow(void)
{
	Server*	server = _response->get_server();

}

std::string	Header::get_current_time(void)
{
	std::time_t currentTime = std::time(0);
	std::tm* timeInfo = std::gmtime(&currentTime);
	char buffer[80];
	std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
	return (std::string(buffer));
}

std::string	Header::file_last_modified_time(std::string file_name)
{
	struct stat	file_info;
	if (stat(file_name.c_str(), &file_info) != 0) {
		std::cerr << "Error getting file information." << std::endl;
		return ("");
	}
	std::tm*	time_info = std::gmtime(&file_info.st_mtime);
	char		buffer[80];
	std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", time_info);
	return (std::string(buffer));
}

std::string	Header::get_str(void) const {return (_str);}
void		Header::set_allow(std::string a) {_allow = a;}
