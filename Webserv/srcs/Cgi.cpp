/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/06 15:10:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Request.hpp"
#include "Header.hpp"
*/
#include "Cgi.hpp"

Cgi::Cgi()
{
	_header = "";
	_full_file_name = "";
	_status_code = 200;
	_location = 0;
	_end = false;
	std::cout << "Cgi Default constructor" << std::endl;
}
Cgi::Cgi(const Cgi& src) { *this = src; }
Cgi&	Cgi::operator=( Cgi const & src )
{
	(void) src;
	return (*this);
}
/*
Cgi::Cgi(int sk, Host* h, Server* s, Request* r) :
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
	std::cout << "Cgi Constructor sk: " << sk << std::endl;
}
*/
Cgi::~Cgi()
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
	std::cout << "Destruction response: " << _socket << std::endl;
}
