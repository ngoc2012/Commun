/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 17:45:46 by ngoc             ###   ########.fr       */
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
ConfigurationParser::ConfigurationParser(std::vector<Server>& servers, const char conf*)
{
	const char*	keys_level_0[] = {"server"}
	const char*	keys_level_1[] = {"listen", "server_name", "location"}
	const char*	keys_location[] = {"listen", "server_name", "location"}

	std::ifstream conf_file(conf);
	if (!conf_file.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return 1;
	}
	Server	*new_server = 0;
	std::string line;
	while (std::getline(conf_file, line)) {
		if (line.c_str()[0] == '#')
			;
		else if (line.substr(0, 6) == std::string("server"))
			Server	*new_server = new Server();
		else if (line.substr(0, 7) == std::string("	listen"))
	}
	inputFile.close();
}
