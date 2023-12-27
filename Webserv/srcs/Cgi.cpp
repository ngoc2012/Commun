/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/27 06:58:52 by ngoc             ###   ########.fr       */
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

    envs["REQUEST_METHOD"] = config_.getMethod();
    envs["REQUEST_URI"] = file_path_;

    envs["SCRIPT_NAME"] = cgi_path_;
    envs["SERVER_NAME"] = config_.getHost();
    envs["SERVER_PROTOCOL"] = config_.getProtocol();
    envs["SERVER_PORT"] = ft::to_string(config_.getPort());
    envs["SERVER_SOFTWARE"] = "WEBSERV/1.0";

    if (extension_ == ".php")
        envs["REDIRECT_STATUS"] = "200";

    for (std::map<std::string, std::string, ft::comp>::iterator it = req_headers_.begin(); it != req_headers_.end(); it++) {
        if (!it->second.empty()) {
            std::string header = "HTTP_" + ft::to_upper(it->first);
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
