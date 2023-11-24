/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 14:55:42 by ngoc             ###   ########.fr       */
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
Header::Header(int e, Response* r) : _err_code(e), _response(r)
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
	_str += "HTTP/1.1 ";
	_str += to_string(e) + " ";
	if (_status.find(e) == _status.end())
		_str += "Unknown error code";
	else
		_str += _status[e];
	_str += "\r\n";
	//_str += 
	std::cout << "Header Constructor" << std::endl;
}
Header::~Header()
{
	std::cout << "Header Destruction" << std::endl;
}

std::string	Header::get_current_time(void)
{
	std::time_t currentTime = std::time(0);
	std::tm* timeInfo = std::gmtime(&currentTime);
	char buffer[80];
	return (std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo));
}

std::string	Header::file_last_modified_time(void)
{
	struct stat fileInfo;
	if (stat(filename, &fileInfo) != 0) {
		std::cerr << "Error getting file information." << std::endl;
		return 1;
	}
	std::tm* timeInfo = std::gmtime(&fileInfo.st_mtime);
	char buffer[80];
	std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
}

std::string	get_str(void) const {return (_str);}
