/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 22:26:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigurationParser.hpp"

ConfigurationParser::ConfigurationParser() {}
ConfigurationParser::ConfigurationParser(const ConfigurationParser& src) { *this = src; }
ConfigurationParser&	ConfigurationParser::operator=( ConfigurationParser const & src )
{
	(void) src;
	return (*this);
}
ConfigurationParser::~ConfigurationParser() {}
void	conf_file_error(std::vector<Server*>& servers, std::string line, int i)
{
	for (std::vector<Server*>::iterator it = servers.begin() ; it != servers.end(); ++it)
		delete (*it);
	std::cerr << "Configuration file error at line " << i << " :" << line << std::endl;
}
ConfigurationParser::ConfigurationParser(std::vector<Server*>& servers, const char* conf)
{
	//const char*	keys_server[] = {"listen", "server_name", "location"};
	//const char*	keys_location[] = {"methods", "client_max_body_size", "client_body_buffer_size", "fastcgi_pass", "fastcgi_param", "include"};
	std::ifstream	conf_file(conf);
	if (!conf_file.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return ;
	}
	Server		*new_server = 0;
	int		i = 0;
	std::string	line;
	while (std::getline(conf_file, line)) {
		i++;
		if (line.c_str()[0] == '#')
			;
		else if (line.substr(0, 6) == std::string("server"))
		{
			new_server = new Server();
			servers.push_back(new_server);
		}
		else if (line.substr(0, 7) == std::string("	listen"))
		{
			if (!new_server)
			{
				conf_file_error(servers, line, i);
				return ;
			}
			std::vector<std::string>	tokens = split_string(line, std::string(" 	"));
			std::vector<std::string>	tokens0 = split_string(tokens[1], std::string(" 	"));
			new_server.set_ip_address(tokens0[1]);
			std::cout << line << std::endl;
		}
	}
	conf_file.close();
}
