/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 12:59:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "webserv.hpp"

#include "RequestHeader.hpp"

RequestHeader::RequestHeader()
{
	std::cout << "RequestHeader Default constructor" << std::endl;
}
RequestHeader::RequestHeader(const RequestHeader& src) { *this = src; }
RequestHeader&	RequestHeader::operator=( RequestHeader const & src )
{
	(void) src;
	return (*this);
}
RequestHeader::~RequestHeader()
{
	std::cout << "RequestHeader Destruction" << std::endl;
}

bool	RequestHeader::parse_method_url(std::string& s, std::string& url, e_method& m)
{
    _pos = s.find("\n");
    if (_pos == NPOS)
        return (false);

    std::vector<std::string>	line0;
    line0 = ft::split_string(s.substr(0, newline), "     ");
    if (line0.size() != 3)
    {
        std::cerr << "Error: First line header invalid" << std::endl;
        return (false);
    }
    url = line0[1];
    if (line0[0] == "GET")
        m = GET;
    else if (line0[0] == "POST")
        m = POST;
    else if (line0[0] == "PUT")
        m = PUT;
    else if (line0[0] == "DELETE")
        m = DELETE;
    else
    {
        std::cerr << "Error: Method unknown : " << line0[0] << std::endl;
        return (false);
    }
    /*
    size_t  newline1 = s.find("\n", newline + 1);
    if (newline == NPOS)
        return (false);

    std::vector<std::string>	line0;
    line0 = ft::split_string(s.substr(0, newline), "     ");
    */
    return (true);
}

bool	    RequestHeader::parse_content_type(Host* host, std::string &s, std::string& ct)
{
    size_t	pos = s.find("Content-Type:");
    if (pos == NPOS)
    {
        std::cerr << "Error: Content type not found." << std::endl;
        return (false);
    }
    std::string type = s.substr(pos + 14, 50);
    std::map<std::string, std::string>*	mimes = host->get_mimes();
    for (std::map<std::string, std::string>::iterator it = mimes->begin();
            it != mimes->end(); ++it)
        if (type.find(it->second) != NPOS)
        {
            ct = it->second;
            return (true);
        }
    std::cerr << "Error: Content type not found." << std::endl;
    return (false);
}

bool	RequestHeader::parse_content_length(std::string& s, size_t& cl)
{
	size_t	pos1;
	size_t	pos = s.find("Content-Length: ");
	if (pos != NPOS)
        pos1 = s.substr(pos).find("\n");
	if (pos == NPOS || pos1 == NPOS)
	{
        std::cerr << "Error: Content length not found." << std::endl;
        return (false);
	}
    pos += 16;
    cl = std::atoi(s.substr(pos, pos1).c_str());
    return (true);
}

void	RequestHeader::set_host(Host* h) {_host = h;}
void    RequestHeader::set_str(std::string* s) {_str = s;}
