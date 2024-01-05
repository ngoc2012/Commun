/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 15:23:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
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

bool	RequestHeader::parse_method_url(std::string& url, e_method& m)
{
    _pos = s.find("\n");
    if (_pos == NPOS)
    {
        std::cerr << "Error: No newline." << std::endl;
        return (false);
    }
    std::vector<std::string>	line0;
    words = ft::split_string(s.substr(0, _pos), "     ");
    if (words.size() != 3)
    {
        std::cerr << "Error: First line header invalid." << std::endl;
        return (false);
    }
    url = words[1];
    if (words[0] == "GET")
        m = GET;
    else if (words[0] == "POST")
        m = POST;
    else if (words[0] == "PUT")
        m = PUT;
    else if (words[0] == "DELETE")
        m = DELETE;
    else
    {
        std::cerr << "Error: Method unknown : " << words[0] << std::endl;
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

std::string	    RequestHeader::parse_host_name()
{
    size_t  last_pos = _pos + 1;

    _pos = s.find("\n", last_pos);
    if (_pos == NPOS)
    {
        std::cerr << "Error: No newline for host name." << std::endl;
        return ("");
    }
    std::vector<std::string>	words;
    words = ft::split_string(s.substr(last_pos, _pos), "     ");
    if (words.size() != 2)
    {
        std::cerr << "Error request header: Host line invalid." << std::endl;
        return ("");
    }
    return (words[1])
}

std::string	    RequestHeader::parse_content_type()
{
    size_t  last_pos = s.find("Content-Type:", last_pos);
    if (_pos == NPOS)
    {
        std::cerr << "Error: Content type not found." << std::endl;
        return ("");
    }
    _pos = _str.find("\n", last_pos);
    words = ft::split_string(s.substr(last_pos, _pos), "     ;");
    if (words.size() != 2)
    {
        std::cerr << "Error request header: Content-Type line invalid." << std::endl;
        return ("");
    }
    std::set<std::string>*	set_mimes = _host->get_set_mimes();
    if (set_mimes->find(words[1]) != set_mimes->end())
        return (words[1]);
    std::cerr << "Error: Content type not found." << std::endl;
    return ("");
    /*
    for (std::map<std::string, std::string>::iterator it = mimes->begin();
            it != mimes->end(); ++it)
        if (type.find(it->second) != NPOS)
        {
            ct = it->second;
            return (true);
        }
    std::cerr << "Error: Content type not found." << std::endl;
    return (false);
    */
}

size_t	RequestHeader::parse_content_length(std::string& s, size_t& cl)
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
