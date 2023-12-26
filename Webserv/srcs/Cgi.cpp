/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/26 17:13:29 by ngoc             ###   ########.fr       */
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
    if (config_.getMethod() == "POST") {
        cgi_env_["CONTENT_TYPE"] = req_headers_["Content-Type"];
        cgi_env_["CONTENT_LENGTH"] = ft::to_string(req_body_.length());
    }
    cgi_env_["GATEWAY_INTERFACE"] = "CGI/1.1";
    cgi_env_["PATH_INFO"] = file_path_;
    cgi_env_["PATH_TRANSLATED"] = file_path_;
    cgi_env_["QUERY_STRING"] = config_.getQuery();
    cgi_env_["REMOTE_ADDR"] = config_.getClient().getAddr();

    if (config_.getAuth() != "off") {
        cgi_env_["AUTH_TYPE"] = "Basic";
        cgi_env_["REMOTE_IDENT"] = config_.getAuth().substr(0, config_.getAuth().find(':'));
        cgi_env_["REMOTE_USER"] = config_.getAuth().substr(0, config_.getAuth().find(':'));
    }

    cgi_env_["REQUEST_METHOD"] = config_.getMethod();
    cgi_env_["REQUEST_URI"] = file_path_;

    cgi_env_["SCRIPT_NAME"] = cgi_path_;
    cgi_env_["SERVER_NAME"] = config_.getHost();
    cgi_env_["SERVER_PROTOCOL"] = config_.getProtocol();
    cgi_env_["SERVER_PORT"] = ft::to_string(config_.getPort());
    cgi_env_["SERVER_SOFTWARE"] = "WEBSERV/1.0";

    if (extension_ == ".php")
        cgi_env_["REDIRECT_STATUS"] = "200";

    for (std::map<std::string, std::string, ft::comp>::iterator it = req_headers_.begin(); it != req_headers_.end(); it++) {
        if (!it->second.empty()) {
            std::string header = "HTTP_" + ft::to_upper(it->first);
            std::replace(header.begin(), header.end(), '-', '_');
            cgi_env_[header] = it->second;
        }
    }

    if (!(env_ = (char **)malloc(sizeof(char *) * (cgi_env_.size() + 1))))
        return false;

    int i = 0;

    for (std::map<std::string, std::string>::iterator it = cgi_env_.begin(); it != cgi_env_.end(); it++) {
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
