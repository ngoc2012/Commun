/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 10:35:43 by ngoc             ###   ########.fr       */
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
//void	conf_file_error(std::vector<Server*>& servers, std::string line, int i)
//{
//	for (std::vector<Server*>::iterator it = servers.begin() ; it != servers.end(); ++it)
//		delete (*it);
//	std::cerr << "Configuration file error at line " << i << " :" << line << std::endl;
//}

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
			if (!new_server || !listen(new_server, line))
				break ;
		}
	}
	conf_file.close();
}

int	ConfigurationParser::listen(Server* s, std::string line)
{
	std::vector<std::string>	listen = split_string(line, std::string(" 	"));
	if (listen.size() != 2)
		return (0);
	std::vector<std::string>	address = split_string(listen[1], std::string(":"));
	if (address.size() != 2)
		return (0);
	std::vector<std::string>	ip = split_string(address[1], std::string(":"));
	if (ip.size() != 4)
		return (0);
	int	n;
	for (int j = 0; j < 4; j++)
	{
		n = std::atoi(ip[j].c_str());
		if (n < 0 || n > 255)
			return (0);
	}
	n = std::atoi(address[1].c_str());
	if (n < 0 || n > 65535)
		return (0);
	s->set_ip_address(address[0]);
	s->set_port(std::atoi(address[1].c_str()));
	std::cout << s->get_ip_address() << ":" << s->get_port() << std::endl;
	return (1);
}
