/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/27 08:24:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Header.hpp"
*/
#include "Request.hpp"

#include "Cgi.hpp"

Cgi::Cgi()
{
	std::cout << "Cgi Default constructor" << std::endl;
}
Cgi::Cgi(const Cgi& src) { *this = src; }
Cgi&	Cgi::operator=( Cgi const & src )
{
	(void) src;
	return (*this);
}
//Cgi::Cgi(Request* r) : _request(r)
//{
//    _request = r;
//}

void    Cgi::envs()
{
    std::map<std::string, std::string>  envs;

    if (config_.getMethod() == "POST") {
        envs["CONTENT_TYPE"] = _request->get_content_type();
        envs["CONTENT_LENGTH"] = ft::itos(_request->get_content_length());
    }
    envs["GATEWAY_INTERFACE"] = "CGI/1.1";
    envs["PATH_INFO"] = _file;
    envs["PATH_TRANSLATED"] = _file;
    envs["QUERY_STRING"] = "";
    envs["REMOTE_ADDR"] = "";
    //envs["QUERY_STRING"] = config_.getQuery();
    //envs["REMOTE_ADDR"] = config_.getClient().getAddr();

    if (config_.getAuth() != "off") {
        envs["AUTH_TYPE"] = "Basic";
        envs["REMOTE_IDENT"] = "";
        envs["REMOTE_USER"] = "";
        //envs["REMOTE_IDENT"] = config_.getAuth().substr(0, config_.getAuth().find(':'));
        //envs["REMOTE_USER"] = config_.getAuth().substr(0, config_.getAuth().find(':'));
    }

    envs["REQUEST_METHOD"] = Location::get_method_str(_request->get_method());
    envs["REQUEST_URI"] = _request->get_url();

    Host*   host = _request->get_host();
    envs["SCRIPT_NAME"] = _file;
    envs["SERVER_NAME"] = host->get_server_name();
    envs["SERVER_PROTOCOL"] = "";
    envs["SERVER_PORT"] = ft::itos((int) host->get_port());
    envs["SERVER_SOFTWARE"] = "WEBSERV/1.0";

    if (extension_ == "php")
        envs["REDIRECT_STATUS"] = "200";

    std::vector<std::string> header_lines = ft::split_string(_request->get_header(), "\n");
    std::string     key;

    for (std::map<std::string>::iterator it = header_lines.begin();
            it != header_lines.end(); it++)
    {
        if (it->find(":") != NPOS)
        {
            key = "HTTP_" + std::to_upper(it->first);
            std::replace(header.begin(), header.end(), '-', '_');
            envs[header] = it->second;
        }
    }

    if (!(env_ = (char **)malloc(sizeof(char *) * (envs.size() + 1))))
        return false;

    int i = 0;

    for (std::map<std::string, std::string>::iterator it = envs.begin(); it != envs.end(); it++) {
        std::string tmp = it->first + "=" + it->second;
        if (!(env_[i] = ft::strdup(tmp.c_str())))
            return false;
        i++;
    }
    env_[i] = NULL;
}

void    Cgi::execute()
{
    //int std_in;
    //int std_out;


}
Cgi::~Cgi()
{
	std::cout << "Destruction Cgi" << std::endl;
}

void        Cgi::set_request(Request* r) {_request = r;}
