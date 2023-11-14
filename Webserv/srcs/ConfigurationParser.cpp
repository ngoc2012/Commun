/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 17:37:53 by ngoc             ###   ########.fr       */
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
	std::string line;
	while (std::getline(conf_file, line)) {
		std::cout << "Read line: " << line << std::endl;
	}
	inputFile.close();
}
