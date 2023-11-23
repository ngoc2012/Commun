/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 11:29:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class Host;
class Server;
class Location;

class ConfigurationParser
{
	private:
		ConfigurationParser();
		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser	&operator=(const ConfigurationParser& op);
	public:
		ConfigurationParser(std::vector<Server*>& servers, Host*, const char* conf);
		virtual			~ConfigurationParser();

		bool			listen(Server*, std::vector<std::string>);
		void			conf_file_error(std::string, int);
		std::string		remove_comments(std::string&);
		std::string		remove_spaces_end(std::string&);
		bool			location_parser(std::string, Location*, std::vector<std::string>&);
		bool			server_parser(std::string, Server*, std::vector<std::string>&);
		bool			host_parser(std::string, Host*, std::vector<std::string>&);
};

#endif
