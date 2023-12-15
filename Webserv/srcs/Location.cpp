/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/15 13:05:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Host.hpp"

Location::Location()
{
}
Location::Location(const Location& src) { *this = src; }
Location&	Location::operator=( Location const & src )
{
	(void) src;
	return (*this);
}
Location::Location(std::string u): _url(u) {}
Location::~Location() {}


Location*	Location::find_location(std::string url, std::vector<Location*> locations, e_method method, int &status_code)
{
	for (std::vector<Location*>::iterator it = locations.begin();
		it != locations.end(); ++it)
	{
		if ((*it)->compare_url(url, (*it)->get_url()))
		{
			if ((*it)->find_method(method, *it))
				status_code = 200;
			else
				status_code = 405; // Method not allowed
            return (*it);
		}
	}
    status_code = 404; // Not found
    return (0);
}

bool	Location::compare_url(std::string url, std::string l_url)
{
	//std::cout << url << "==" << l_url << std::endl;
	// Folder
	if (l_url[l_url.size() - 1] == '/')
	{
		if (url == l_url || url == l_url.substr(0, l_url.size() - 1)
			|| (url.size() > l_url.size()
                && url.substr(0, l_url.size()) == l_url))
			return (true);
	}
	// File
	else if (url == l_url)
		return (true);
    if (l_url.find('*') != NPOS
            && match_wildcard(url.c_str(), l_url.c_str()))
		return (true);
	return (false);
}

bool	Location::find_method(e_method m, Location* loc)
{
	std::vector<e_method>	methods = loc->get_methods();

	for (std::vector<e_method>::iterator	it = methods.begin();
		it != methods.end(); ++it)
		if (m == *it)
			return (true);
	//std::cout << _request->get_method() << "==" << *it << std::endl;
	return (false);
}

std::string	Location::get_full_file_name(std::string url, std::string root)
{
    std::string file_name;

    if (_alias == "")
        file_name += root;
    else
        file_name += _alias;
    if (url.size() > _url.size())
        file_name += url.substr(_url.size(), url.size() - 1);
	struct stat	info;
	if (stat(file_name.c_str(), &info) == 0
            && S_ISDIR(info.st_mode))
		file_name += "index.html";
    return (file_name);
	//std::cout << _full_file_name << std::endl;
}

std::string	Location::get_methods_str(void)
{
	std::string	s = "";
	for(std::vector<e_method>::iterator it = _methods.begin();
            it != _methods.end(); ++it)
	{
		if (it != _methods.begin())
			s += ",";
		switch (*it)
		{
			case GET:
				s += "GET";
				break;
			case POST:
				s += "POST";
				break;
			case PUT:
				s += "PUT";
				break;
			case NONE:
				s += "NONE";
				break;
		}
	}
	return (s);
}

std::vector<e_method>		Location::get_methods(void) const {return (_methods);}
std::string			Location::get_alias(void) const {return (_alias);}
std::string			Location::get_url(void) const {return (_url);}
std::string			Location::get_cgi_pass(void) const {return (_cgi_pass);}

void				Location::insert_methods(e_method e) {_methods.push_back(e);}
void				Location::set_alias(std::string s) {_alias = s;}
void				Location::set_url(std::string u) {_url = u;}
void			    Location::set_cgi_pass(std::string c) {_cgi_pass = c;}
