/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 18:31:56 by ngoc             ###   ########.fr       */
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
void	conf_file_error(std::vector<Server>& servers, std::string line, int i)
{
	for (std::vector<Server>::iterator it = servers.begin() ; it != servers.end(); ++it)
		delete (&it);
	std::cerr << "Configuration file error at line " << i << " :" << line << std::endl;
}
ConfigurationParser::ConfigurationParser(std::vector<Server>& servers, const char* conf)
{
	//const char*	keys_server[] = {"listen", "server_name", "location"};
	//const char*	keys_location[] = {"methods", "client_max_body_size", "client_body_buffer_size", "fastcgi_pass", "fastcgi_param", "include"};
	std::ifstream	conf_file(conf);
	if (!conf_file.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return ;
	}
	Server	*new_server = 0;
	int	i = 0;
	std::string line;
	while (std::getline(conf_file, line)) {
		i++;
		if (line.c_str()[0] == '#')
			;
		else if (line.substr(0, 6) == std::string("server"))
			Server	*new_server = new Server();
		else if (line.substr(0, 7) == std::string("	listen"))
		{
			if (!new_server)
				return (conf_file_error(servers, line, i));
			std::cout << line << std::endl;
		}
	}
	inputFile.close();
}
